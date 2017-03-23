/**
 * comp2129 - assignment 2
 * Hongliang pan
 * hpan8385
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "snapshot.h"

//initialize entry linked list
entry* entry_head = NULL;
entry* entry_tail = NULL;
//initialize snapshot linked list
snapshot* snapshot_head = NULL;
snapshot* snapshot_tail = NULL;
int i = 1;
// ************************************************************
void fuckAllValues(value *value){
	if(value->next != NULL)
    	{
    		// not end of values
		fuckAllValues(value->next);
		free(value);
   	}else{
   		// end of values
		free(value);
    	}
    	return;
}

// ************************************************************
void fuckAllEntries(entry *entry){
	if(entry->next != NULL){
		// not entry tail

		// not entry head
		if(entry->values != NULL)
		fuckAllValues(entry->values);

		fuckAllEntries(entry->next);
		free(entry);
	}else{
		// entry tail
		free(entry);
	}
	return;
}

// ************************************************************

//bye function end the program
void bye() {
    printf("bye\n");
    
	fuckAllEntries(entry_head);	
	exit(0);
	
	
}

//show the help list
void help() {
    printf("%s\n", HELP);
    
	return;
}
//record entry in entry linked list
void set(char *key, value *newValue) {
		entry* current = entry_head->next;
		while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
						value* temp = current->values;
						current->values = newValue;
						free(temp);
						printf("ok\n\n");
						return;
					}
					current = current->next;
					
					
		}
		int i;
   		// store key
		for (i = 0; i < MAX_KEY; i++) {
		entry_tail->key[i] = key[i];
			if (key[i] == '\0') {
				break;
			}
		}
		//store the value from entry_tail
		entry_tail->values = newValue;


		// Create new entry_tail;
		entry_tail->next = (entry *) malloc(sizeof(entry));
		entry_tail->next->prev = entry_tail;
		entry_tail->next->next = NULL;
		entry_tail->next->values = NULL;

		entry_tail = entry_tail->next;
		printf("ok\n\n");
		return;
	
}
//show the keys
void list_keys() {
	if (entry_head->next->next == NULL) {
            printf("no keys\n\n");
    } else {
        entry *current = entry_tail->prev;
        while (current->prev != NULL) {
            printf("%s\n", current->key);
            current = current->prev;
    	}
		printf("\n");
    }
	return;
} 
//show exsiting entries
void list_entries() {
	if (entry_head->next->next == NULL) {
        printf("no entries\n\n");
    } else {
        entry *current = entry_tail->prev;
        while (current->prev != NULL) {
            printf("%s [", current->key);
            // print first num
            value *currentValue = current->values; 
            printf("%d", currentValue->value);
            // print second num and go on (if exist)
            while (currentValue->next != NULL) {
                currentValue = currentValue->next;
                printf(" %d", currentValue->value);
            }
            printf("]\n");
            current = current->prev;
    	}
		printf("\n");
    }
	return;
}
void list_snapshots(){
		printf("no snapshots\n\n");
}
//show the key and its values
void get(char *key){
	if (entry_head->next->next == NULL) {
        printf("no such key\n\n");
	}else{
       	entry* current = entry_head->next;
       	while(current->next != NULL){
       		if (current->next != NULL && strcmp(current->key, key) == 0){
       			value *currentvalues = current->values;
				
				if(currentvalues == NULL){
						printf("[]\n\n");
						return;
				}else {
						printf("[%d", currentvalues->value);
						while(currentvalues->next != NULL){
						currentvalues = currentvalues->next;
						printf(" %d",currentvalues->value);
						}
						printf("]\n\n");
						return;
				}
       		}
		
       			
		current = current->next;
		}
		
		printf("no such key\n\n");
			return;
     }
}
       
//delete the key and its values
void del(char *key){
	if (entry_head->next->next == NULL) {
        printf("no such key\n\n");
       }else{
       		entry* current = entry_head->next;
       		while(current != NULL){
       			if (strcmp(current->key, key) == 0){
       				current->prev->next = current->next;
       				current->next->prev = current->prev;
       				printf("ok\n\n");
					fuckAllValues(current->values);
					free(current);
       				return;
       			}
       			current = current->next;

       		}
       		printf("no such key\n\n");
       }
}

//add values to entry linked list from the front
int push(char *key,int a){
		if (entry_head->next->next == NULL) {
        
			return 0;
       	}else{
			entry* current = entry_head->next;
			
			while(current->next!= NULL){
				if(current->next != NULL && strcmp(current->key, key) == 0){
					value *newValue = (value *) malloc(sizeof(value));
					value *currentvalues = newValue;
					currentvalues->value = a;
					currentvalues->next = current->values;
					current->values = currentvalues;
					
					return 1;
					
				}
				
				current= current->next;
			}
			
				return 0;
		}
}
//add values from the end
void append(char *key,value *newValue){
		if (entry_head->next->next == NULL) {
        	free(newValue);
			printf("no such key\n\n");
        }else{
			
			entry* current = entry_head->next;
			
			while(current->next!= NULL){
				if(current->next != NULL &&strcmp(current->key, key) == 0){
					value *currentvalues = current->values;
					while(currentvalues->next != NULL){
						currentvalues = currentvalues->next;
					}
						currentvalues->next = newValue;
						printf("ok\n\n");
						return;
				}
					current= current->next;
			}
	    		free(newValue);
			printf("no such key\n\n");
		}
}
//display value at index
void pick(char *key,int index){
		if (entry_head->next->next == NULL) {
        printf("no such key\n\n");
        }else {
			 entry* current = entry_head->next;
			 while(current->next!= NULL){
				if(current->next != NULL && strcmp(current->key, key) == 0){
					 value *currentValue = current->values;
						int i = 1;
						while(i != index){
						
								if(currentValue->next == NULL){
									printf("index out of range\n\n");
									return;
								}
							currentValue = currentValue->next;
							i++;
						}
						printf("%d\n\n",currentValue->value);
						return;
				}
						current= current->next;
			}
			printf("no such key\n\n");	
	     }
}
//declare pop function
void pop(char *key);

//display and remove value at index
void pluck(char *key,int index){
			if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
			}else {
				entry* current = entry_head->next;
				while(current->next!= NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){

						if(index == 1){
								pop(key);
								return;
							}else{
							// ***************************************************************
							// find the value to be deleted
							value *value_to_be_deleted = current->values;
							for(int i = 0; i < index-1; i ++){
								if(value_to_be_deleted->next != NULL){
									value_to_be_deleted = value_to_be_deleted->next;
								}else{
									printf("index out of range\n\n");
									return;
								}
							}
							printf("%d\n\n",value_to_be_deleted->value);

							// find the value BEFORE the value to be deleted
							value *value_before = current->values;
							for(int i = 0; i < index-2; i ++){
								value_before = value_before->next;
							}		

							// delete
							value_before->next = value_to_be_deleted->next;
							free(value_to_be_deleted);

							return;	
							// *************************************************************
						}
					}
					current= current->next;
				}
				printf("no such key\n\n");
			}

			
}
//display and removes the first value of the key
void pop(char* key){
			if (entry_head->next->next == NULL){ 
        		printf("no such key\n\n");
			}else {
				entry* current = entry_head->next;
				while(current->next != NULL){
						if(current->next != NULL && strcmp(current->key, key) == 0){
							 
							 if (current->values == NULL)
							 {printf("nil\n\n");
								return;
							 }
							 else {
						     	 if (current->values->next == NULL)
								 {printf("%d\n\n",current->values->value);
									 	free(current->values);
								  
								  		current->values = NULL;
								  		return;
								 }else{
									printf("%d\n\n",current->values->value);
								 	 value *temp_need_free_value = current->values;
									 
									 current->values = current->values->next;
									 free(temp_need_free_value);
								 	
								 }
								 return;
							 }	
						}
					current= current->next;
				}
				printf("no such key\n\n");
			}
}

//display the minimum value of the key
void min(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
						value* currentvalue = current->values;
						int a;
						a = currentvalue->value;
						while(currentvalue != NULL){
								if(a > currentvalue->value){
									a = currentvalue->value;
									
								}
								else{
									currentvalue = currentvalue->next;
								}
						}
						printf("%d\n\n",a);
						return;
					}
						current = current->next;
			}
			printf("no such key\n\n");
		}
}

//display maximum value
void max(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
						value* currentvalue = current->values;
						int a;
						a = currentvalue->value;
						while(currentvalue != NULL){
								if(a < currentvalue->value){
									a = currentvalue->value;
								}
								else{
									currentvalue = currentvalue->next;
								}
						}
						printf("%d\n\n",a);
						return;
					}
					current = current->next;
			}
			printf("no such key\n\n");
		}
}

//display sum of values
void sum(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
							value* currentvalue = current->values;
							int a = 0;
							while(currentvalue != NULL){
								a = a + currentvalue->value;
								currentvalue = currentvalue->next;
							}
							printf("%d\n\n",a);
							return;
					}	
					current = current->next;
			}
			printf("no such key\n\n");
		}

}
//displays number of values
void len(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
							value* currentvalue = current->values;
							int a = 0;
							while(currentvalue != NULL){
								a = a + 1;
								currentvalue = currentvalue->next;
							}
							printf("%d\n\n",a);
							return;
					}	
					current = current->next;
			}
			printf("no such key\n\n");
		}
}


void rev(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
				entry* current = entry_head->next;
				while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
							value* currentvalue = current->values;
							int a[100],i=0;
							while(currentvalue != NULL){
									a[i] = currentvalue->value;
									
									i++;
									currentvalue = currentvalue->next;
							}
							
							value *revValue = (value *) malloc(sizeof(value));
							value *currentRevValue = revValue;

							i--;
							for(; i > 0; i --){
								currentRevValue->value = a[i];
								currentRevValue->next = (value *) malloc(sizeof(value));
								currentRevValue = currentRevValue->next;
							}
                            // handle the last value
                            currentRevValue->value = a[i];
							currentRevValue->next = NULL;

							// FREE 
							fuckAllValues(current->values);

							current->values = revValue;
							printf("ok\n\n");
							return;
					
					}	
					current = current->next;
			}
			printf("no such key\n\n");
		}
}

//removes repeated adjacent values
void uniq(char* key){
		if (entry_head->next->next == NULL) {
        	
			printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
							value* currentvalue = current->values;
							while(currentvalue->next != NULL){
									if(currentvalue->value == currentvalue->next->value){
										value* temp = currentvalue->next;
										
										currentvalue->next = currentvalue->next->next;
										free(temp);
									}else{
										currentvalue = currentvalue->next;
									}
							}
						printf("ok\n\n");
						return;
					}	
					current = current->next;
			}
			
			printf("no such key\n\n");
		}

}

//sorts values in ascending values
void sort(char* key){
		if (entry_head->next->next == NULL) {
        		printf("no such key\n\n");
		}else{
			entry* current = entry_head->next;
			while(current->next != NULL){
					if(current->next != NULL && strcmp(current->key, key) == 0){
							value* currentvalue = current->values;
							value* currentValue = current->values;
						while(currentValue->next != NULL){
							while(currentvalue->next != NULL){
									if (currentvalue->value > currentvalue->next->value){
										int a = currentvalue->next->value;
										currentvalue->next->value = currentvalue->value;
										currentvalue->value = a;
										
										currentvalue = currentvalue->next;
									}else{
										currentvalue = currentvalue->next;
									}
							}
							currentValue = currentValue->next;
							currentvalue = current->values;
						}
						printf("ok\n\n");
						return;
					}	
					current = current->next;
			}
			printf("no such key\n\n");
		}

}
/*void diff(char *key1,char *key2){
		if (entry_head->next->next == NULL) {
        	printf("no such key\n");
		}else{
			entry* current1 = entry_head->next;
			entry* current2 = entry_head->next;
			while(current1->next != NULL ){
				if(current1->next != NULL && strcmp(current1->key, key1) == 0)
						break;
				else{
				current1 = current1->next;
				}	
			}
			while(current2->next != NULL ){
				if(current2->next != NULL && strcmp(current2->key, key2) == 0)
						break;
				else{
				current2 = current2->next;
				}			
			}
			if(current1->next == NULL || current2->next == NULL){
							printf("no such key\n\n");
			}
			else{
				value* currentvalue1 = current1->values;
				value* currentvalue2 = current2->values;
				printf("[");
				while(currentvalue1 != NULL){
						while(currentvalue2 != NULL){
							if (currentvalue1->value == currentvalue2->value)
									break;
							else{
								currentvalue2 = currentvalue->next;
							}
						}
					  
					   currentvalue1 = currentvalue1->next;
					   currentvalue2 = current2->values;
				}
				printf("]\n\n");
			}	
		}
}*/
/*void inter(char *key1,char *key2){
		if (entry_head->next->next == NULL) {
        	printf("no such key\n");
		}else{
			entry* current1 = entry_head->next;
			entry* current2 = entry_head->next;
			while(current1->next != NULL ){
				if(current1->next != NULL && strcmp(current1->key, key1) == 0)
						break;
				else{
				current1 = current1->next;
				}	
			}
			while(current2->next != NULL ){
				if(current2->next != NULL && strcmp(current2->key, key2) == 0)
						break;
				else{
				current2 = current2->next;
				}			
			}
			if(current1->next == NULL || current2->next == NULL){
							printf("no such key\n\n");
			}
			else{
				value* currentvalue1 = current1->values;
				value* currentvalue2 = current2->values;
				printf("[");
				while(currentvalue1 != NULL){
						while(currentvalue2 != NULL){
							if (currentvalue1->value == currentvalue2->value){
									
									if(currentvalue1->next == NULL){
											printf("%d",currentvalue1->value);
												break;
									}
									printf("%d ",currentvalue1->value);
									currentvalue2 = currentvalue2->next;
							}
							else{
									currentvalue2 = currentvalue2->next;
							}
						}
					   currentvalue1 = currentvalue1->next;
					   currentvalue2 = current2->values;
				}
				printf("]\n\n");
			}	
		}
}*/

void purge(){
		printf("ok\n\n");
}
int main(){
	
	char line[MAX_LINE];
	char *input;
	char *key;
	int num;
	
	// entry_head is always empty. When add element, modify entry_tail, and create a new entry_tail
	//allocate address to entry_head and entry_tail
	entry_head = (entry *) malloc(sizeof(entry));
	entry_tail = (entry *) malloc(sizeof(entry));
	//initialize entry_head and entry_tail
	entry_head->prev = NULL;
	entry_head->values = NULL;
	entry_head->next = entry_tail;
	entry_tail->prev = entry_head;
	entry_tail->next = NULL;
	entry_tail->values = NULL;
	
	
	
	
	
	//keep getting new line
	
	while(1) {
    	printf("> ");
		fgets(line, MAX_LINE, stdin);
    	//split the string
		
		input = strtok(line, " "); 
    	
		if (strcasecmp(input, "BYE\n") == 0) {
			bye();
		}
		
		else if (strcasecmp(input, "HELP\n") == 0) {
			help();
		}
		else if (strcasecmp(input, "LIST") == 0) {
			input = strtok(NULL, " ");
				if (strcasecmp(input, "KEYS\n") == 0) {
				list_keys();
				}
				else if (strcasecmp(input, "ENTRIES\n") == 0) {
				list_entries();
				}
				else if (strcasecmp(input, "SNAPSHOTS\n") == 0) {
				list_snapshots();
				}
		}
		else if(strcasecmp(input, "GET") == 0){
			key = strtok(NULL, "\n");
			get(key);
		}
		else if (strcasecmp(input, "DEL") == 0){
			key = strtok(NULL, "\n");
			del(key);
		}
		else if (strcasecmp(input, "PUSH") == 0){
			key = strtok(NULL, " ");
			
			input = strtok(NULL, " ");
			int a = strtol(input, NULL, 10);
			if(push(key,a) == 0){
				printf("no such key\n\n");
				
			}
			else {
				input = strtok(NULL, " ");
				while(input != NULL){
				
				a = strtol(input, NULL, 10);
				push(key,a);
				input = strtok(NULL, " ");
				}
				printf("ok\n\n");
			}
			
		}
			
		else if(strcasecmp(input, "APPEND") == 0){
			key = strtok(NULL, " ");
			
			value *newValue = (value *) malloc(sizeof(value));
			value *currentValue = newValue;
			
			
			// first num
			input = strtok(NULL, " ");
			num = strtol(input, NULL, 10);
			currentValue->value = num; 
			currentValue->next = NULL;
			// second num (or NULL)
			input = strtok(NULL, " ");
			while(input != NULL) {
				num = strtol(input, NULL, 10);
				currentValue->next = (value *) malloc(sizeof(value));
				currentValue = currentValue->next;
				currentValue->value = num;
				currentValue->next = NULL;
				input = strtok(NULL, " ");
			}
			append(key,newValue);
		}
		
		else if (strcasecmp(input, "PICK") == 0){
				key = strtok(NULL, " ");
				input = strtok(NULL, " ");
				int index = strtol(input, NULL, 10);
				if(index == 0){
					printf("index out of range\n\n");
				}
				else pick(key,index);
		
		}
		else if (strcasecmp(input, "PLUCK") == 0){
				key = strtok(NULL, " ");
				input = strtok(NULL, " ");
				int index = strtol(input, NULL, 10);
				if(index == 0){
					printf("index out of range\n\n");
				}
				else pluck(key,index);
		}
		
		else if (strcasecmp(input, "POP") == 0){
				key = strtok(NULL, "\n");
				pop(key);
		}
		
		else if (strcasecmp(input, "MIN") == 0){
				key = strtok(NULL, "\n");
				min(key);
		}
		
		else if (strcasecmp(input, "MAX") == 0){
				key = strtok(NULL, "\n");
				max(key);
		}
		
		else if (strcasecmp(input, "SUM") == 0){
				key = strtok(NULL, "\n");
				sum(key);
		}
		
		else if (strcasecmp(input, "LEN") == 0){
				key = strtok(NULL, "\n");
				len(key);
		}
		
		else if (strcasecmp(input, "REV") == 0) {
				key = strtok(NULL, "\n");
				rev(key);
		}
		else if	(strcasecmp(input, "UNIQ") == 0) {
				key = strtok(NULL, "\n");
				uniq(key);
		}
		else if (strcasecmp(input, "SORT") == 0) {
				key = strtok(NULL, "\n");
				sort(key);
		}
		
		else if(strcasecmp(input, "PURGE") == 0){
				purge();
		}
		else if (strcasecmp(input, "SET") == 0) {
			value *newValue = (value *) malloc(sizeof(value));
			value *currentValue = newValue;
			
			// set key
			key = strtok(NULL, " ");
			// first num
			input = strtok(NULL, " ");
			num = strtol(input, NULL, 10);
			currentValue->value = num; 
			currentValue->next = NULL;
			// second num (or NULL)
			input = strtok(NULL, " ");
			while(input != NULL) {
				num = strtol(input, NULL, 10);
				currentValue->next = (value *) malloc(sizeof(value));
				currentValue = currentValue->next;
				currentValue->value = num;
				currentValue->next = NULL;
				input = strtok(NULL, " ");
			}
			set(key, newValue);
		}
	}
		return 0;
}










