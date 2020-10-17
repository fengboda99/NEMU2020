#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUMBER_1, MINUS, NUMBER_2, POINTER, REGISTER, VALUE, NEQ, AND, OR

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
	int prior;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE, 0},					// spaces
	{"\\+", '+', 3},					// plus
	{"-", '-', 3}, 						// sub
	{"\\*", '*', 4},					// mul
	{"/", '/', 4},						// div
	{"\\(", '(', 6},					//left
	{"\\)",')', 6},						//right
	{"\\b[0-9]+\\b", NUMBER_1, 0},				//number
	{"\\b0[xX][0-9a-zA-Z]+\\b", NUMBER_2, 0},		//16number
	{"\\$[a-zA-Z]+", REGISTER, 0},                      	//register
	{"\\b[a-zA-Z_0-9]+", VALUE, 0},                      	//value
	{"!=", NEQ, 2},  					//not equal
	{"!", '!', 5},						//not
	{"&&", AND, 1},						//AND
	{"\\|\\|", OR, 0},					//OR
	{"==", EQ, 2}						// equal
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
	int prior;
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;
				
				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case NOTYPE: break;
					
					default: 
						tokens[nr_token].type = rules[i].token_type;
						tokens[nr_token].prior = rules[i].prior;
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						tokens[nr_token].str[substr_len]='\0';
						nr_token++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int l,int r) {
	if(tokens[l].type == '(' && tokens[r].type == ')') {
		int sum=0;
		int i;
		for(i=l+1;i<r;i++) {
			if(tokens[i].type=='(') sum++;
			else if(tokens[i].type == ')') sum--;
			if(sum<0) return false;
		}
		if(sum == 0 ) return true;
	}
	return false;
}

int dominant_operator(int l,int r) {
	int position = l;
	int i;
	int cnt = 0; // count the parentheses
	for(i=r;i>=l;i--) {
		if(tokens[i].type == NUMBER_1||tokens[i].type == NUMBER_2 || tokens[i].type==REGISTER || tokens[i].type==VALUE) continue;
		if(tokens[i].type == ')') {cnt++;continue;}
		else if(tokens[i].type == '(') {cnt--;continue;}
		if(cnt==0) {
			if(position==l&&i!=l&&tokens[i].prior!=6) position = i;
			else if(tokens[i].prior<tokens[position].prior) {
				//printf("%d %d\n",tokens[i].prior,tokens[position].prior);
				position = i;
			}
			else if(tokens[i].prior==5&&tokens[position].prior==5) {
				position = i;
			}	
			else assert(0);
		}
	}
	return position;
}

uint32_t getvalue(char* s,bool* success);

uint32_t eval(int l,int r) {
	//printf("nice %d %d\n",l,r);
	if(l>r) {
		Assert(l>r,"something wrong\n");
		return 0;
	}
	else if(l==r) {
		uint32_t value=-1;
		if(tokens[l].type==NUMBER_1)
			sscanf(tokens[l].str,"%d",&value);
		else if(tokens[l].type==NUMBER_2)
			sscanf(tokens[l].str,"%x",&value);
		else if(tokens[l].type==REGISTER) {
			char *tmp = tokens[l].str+1;
			int i;
			for(i=0;i<8;i++) {
				if(strcmp(tmp,regsl[i])==0) {
					value = reg_l(i);
					break;
				}
				if(strcmp(tmp,regsw[i])==0) {
					value = reg_w(i);
					break;
				}	
				if(strcmp(tmp,regsb[i])==0) {
					value = reg_b(i);
					break;
				}
			}
			if(i==8) {
				if(strcmp(tmp,"eip")==0) {
					value = cpu.eip;
				}
			}
			else assert(1); 	
		}
		else if(tokens[l].type==VALUE) {
			bool ff;
			value = getvalue(tokens[l].str,&ff);
			if(!ff) value = -1;
		}
		else assert(0);
		return value;
	}
	else if(check_parentheses(l,r)==true) return eval(l+1,r-1);
	else {
		int position = dominant_operator(l,r);
		//printf("%d %d %d\n",l,position,r);
		if(tokens[position].type==MINUS||tokens[position].type==POINTER||tokens[position].type=='!') {
			int val = eval(position+1,r);
			//printf("%d\n",val);
			switch(tokens[position].type) {
				case MINUS: return -val;
				case POINTER: return swaddr_read(val,4,R_DS);
				case '!': return !val;
				default: break;
			}
		}
		uint32_t val1 = eval(l,position-1);
		uint32_t val2 = eval(position+1,r);
		//printf("%d %d\n",val1,val2);
		switch(tokens[position].type) {
			case '+': return val1+val2; 
			case '-': return val1-val2;
			case '*': return val1*val2;
			case '/': {int v1 = val1;int v2 = val2; int ans = v1/v2;return ans;}
			case AND: return val1&&val2;
			case OR: return val1||val2;
			case EQ: return val1==val2;
			case NEQ: return val1!=val2;
			default: break;
		}
	} 
	assert(0);
	return -1;
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Insert codes to evaluate the expression. */
	int i;
	for(i=0;i<nr_token;i++) {
		if(tokens[i].type=='-'&&(i==0||(tokens[i-1].type!=NUMBER_1&&tokens[i-1].type!=')'&&tokens[i-1].type!=NUMBER_2&&tokens[i-1].type!=REGISTER&&tokens[i-1].type!=VALUE))) {
			//printf("123\n");
			tokens[i].type = MINUS;
			tokens[i].prior = 5;
		}
		if(tokens[i].type=='*'&&(i==0||(tokens[i-1].type!=NUMBER_1&&tokens[i-1].type!=')'&&tokens[i-1].type!=NUMBER_2&&tokens[i-1].type!=REGISTER&&tokens[i-1].type!=VALUE))) {
			tokens[i].type = POINTER;
			tokens[i].prior = 5;
		}
	}
	*success = true;
	return eval(0,nr_token-1);
}

