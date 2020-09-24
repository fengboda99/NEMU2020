#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp() {
	if(free_==NULL) assert(0);
	WP* tmp  = free_;
	free_ = free_ -> next;
	tmp->val=0;
	tmp->str[0]='\0';
	tmp->next = head;
	head = tmp;

	return tmp;
}

void free_wp(WP* wp) {
	WP* tmp = head;
	bool f= false;
	if(tmp==NULL) assert(0);
	while(tmp!=NULL) {
		if(tmp==wp) {	
			head = head->next;
			f= true;
			break;
		}
		if((tmp->next)==wp) {
			tmp->next = wp->next;
			f = true;
			break;
		}
		else tmp = tmp->next;
	}
	if(!f) assert(0);
	wp->next = free_;
	free_ = wp;
}

void info_wp() {
	WP* tmp = head;
	while(tmp!=NULL) {
		printf("watchpoint %d: %s, the value is %d\n",tmp->NO,tmp->str,tmp->val);
		tmp = tmp->next;
	}
}

void delete_wp(int num) {
	WP* tmp = head;
	bool f = false;
	if(tmp==NULL) assert(0);
	while(tmp!=NULL) {
		if(tmp->NO==num) {
			free_wp(tmp);	
			f=true;
			break;
		}
		else tmp = tmp->next;
	}
	if(!f) assert(0);
}

bool check_wp() {
	WP* tmp = head;
	bool f = false;
	while(tmp!=NULL) {
		bool suc;
		int val = expr(tmp->str,&suc);
		if(val!=tmp->val) {
			f = true;
			printf("OLD value is %d\n",tmp->val);
			printf("NEW value is %d\n",val);
			printf("watchpoint %d has changed\n",tmp->NO);
			tmp->val = val;
		}
		tmp = tmp->next;	
	}
	return f;
}

