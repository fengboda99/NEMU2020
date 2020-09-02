#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUMBER_1, MINUS

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"-", '-'}, 					// sub
	{"\\*", '*'},					// mul
	{"/", '/'},					// div
	{"\\(", '('},					//left
	{"\\)",')'},					//right
	{"\\b[0-9]+\\b", NUMBER_1},			//number
	//{"\\b0[xX][0-9a-zA-Z]+\\b", NUMBER_2},		//16number
	//{"\\b[]", var},
	{"==", EQ}					// equal
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
	int position = -1;
	int i;
	int cnt = 0; // count the parentheses
	for(i=r;i>=l;i--) {
		if(tokens[i].type == NUMBER_1 ) continue;
		if(tokens[i].type == ')') cnt++;
		else if(tokens[i].type == '(') cnt--;
		if(cnt==0) {
			if(position == -1) position = i;
			else if(tokens[position].type=='*' || tokens[i].type=='/') {
				if(tokens[i].type == '+' || tokens[i].type == '-')
					position = i;
			}
		}
	}
	return position;
}

uint32_t eval(int l,int r) {
	if(l>r) {
		Assert(l>r,"something wrong\n");
		return 0;
	}
	else if(l==r) {
		int value;
		sscanf(tokens[l].str,"%d",&value);
		return value;
	}
	else if(check_parentheses(l,r)==true) return eval(l+1,r-1);
	else {
		int position = dominant_operator(l,r);
		if(tokens[position].type == MINUS) {
			int val = eval(position+1,r);
			return -val;
		}
		int val1 = eval(l,position-1);
		int val2 = eval(position+1,r);
		switch(tokens[position].type) {
			case '+': return val1+val2; 
			case '-': return val1-val2;
			case '*': return val1*val2;
			case '/': return val1/val2;
			default: break;
		}
	} 
	assert(1);
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
		if(tokens[i].type=='-'&&(i==0||tokens[i-1].type!=NUMBER_1&&tokens[i].type!=')'))
			tokens[i].type = MINUS;
	}
	*success = true;
	return eval(0,nr_token-1);
}

