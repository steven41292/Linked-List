//Steven Wojcio
//A3
//Brandon Whitehead

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name, grade, gtid)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	char* first_name; /* This will be malloc'd!*/
	char* last_name; /* This will also be malloc'd */
	int grade;
	unsigned int gtid;
} Student;

Student* create_student(const char* first_name, const char* last_name, int grade, unsigned int gtid)
{
	/* First allocate a student on the heap */
	Student* lilGuy=(Student*) malloc(sizeof(Student));
	lilGuy->first_name=malloc((strlen(first_name)+1)*sizeof(char));
	lilGuy->last_name=malloc((strlen(last_name)+1)*sizeof(char));

	/* Allocate enough space for the first and last names */
	/* AND copy the first and last name to the first and last name fields in the struct */
	strncpy(lilGuy->first_name,first_name,(strlen(first_name)+1));
	strncpy(lilGuy->last_name,last_name,(strlen(last_name)+1));
	
	/* Set the grade and gtid */
	lilGuy->grade=grade;
	lilGuy->gtid=gtid;
	/* Notice there are two functions that will help you with the second and third steps */
	/* strlen and strncpy will be helpful */
	/* type man strlen and man strncpy to learn how to use them */

	/* DO NOT store the parameters first_name/last_name in the struct you allocate */ 
	
	return lilGuy;
}

/* For these functions below you should never be passed in NULL */
/* You will always get valid data here */
void print_student(void* data)
{
	/* TODO Implement just print out all of the information here. */
	/* Your output should exactly look like this without no weird characters printing out.
	Student: FIRSTNAME LASTNAME
	Grade: GRADE
	GtID: GTID
	*/
	/* printf and the format specifiers %d %s will be useful here 
	Again use the man pages if you don't know how to use printf */
	
	Student* kid=(Student*) data;

	printf("Student: %s %s\n",kid->first_name,kid->last_name);
	printf("Grade: %d\n",kid->grade);
	printf("GtID: %d\n",kid->gtid);
	
}

void free_student(void* data)
{
	/* TODO Implement You are to first free any fields that were malloc'd. */
	/* Then free the struct in this order */

	Student* kid= (Student*) data;
	free(kid->first_name);
	free(kid->last_name);
	free(kid);
	
}

int student_eq(const void* a, const void* b)
{
	/* TODO Test if two students are equal */
	/* Two students are equal if all of their fields are equal */
	/* To compare strings the function strncmp will be useful */
	/* Again you can read the man pages for strncmp */
	/*Student* sA=(Student*)malloc(sizeof(Student));
	Student* sB=(Student*)malloc(sizeof(Student));
	sA->first_name=malloc((sizeof(((Student*)a)->first_name)+1)*sizeof(char));
	sB->first_name=malloc((sizeof(((Student*)b)->first_name)+1)*sizeof(char));
	sA->last_name=malloc((sizeof(((Student*)a)->last_name)+1)*sizeof(char));
	sB->last_name=malloc((sizeof(((Student*)b)->last_name)+1)*sizeof(char));*/
	
	Student* sA= (Student*) a;
	Student* sB= (Student*) b;
	if(sA->grade==sB->grade){
		if(sA->gtid==sB->gtid){
			if(strncmp(sA->first_name,sB->first_name,(strlen(sA->first_name)+1))==0){
				if(strncmp(sA->last_name,sB->last_name,(strlen(sA->last_name)+1))==0)return 1;
			}	
		}
	}
	//free(sA->first_name);
	//free(sB->first_name);
	//free(sA->last_name);
	//free(sB->last_name);
	//free(sA);
	//free(sB);
	return 0;
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/

int all_A(const void* student){
	Student* kid=(Student*) student;
	if(kid->grade>=90){/*free(kid);*/return 0;}
	else{
	
	return 1;}
}

int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
	

  	/* What does an empty list contain?  Lets use our handy traversal function */
  	
	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Lets add a student and then print */
 	push_front(llist, create_student("Nick", "Polive", 56, 239402128));
 	printf("TEST CASE 2\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	

 	/* Lets remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:");
 	traverse(llist, print_student);
 	printf("\n\n");
	
 	/* Lets add two elements and then print */
 	push_front(llist, create_student("Baron", "von Baris", 92, 123456789));
 	push_back(llist, create_student("George", "Burdell", 65, 902313373));
 	printf("TEST CASE 4\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

 	/* Test find occurence when the node is not found */
	// Notice the commented line below is BAD because the return value from create_student was malloc'd and 	you never free it!
	// find_occurence(llist, create_student("Nurse", "Joy", 3, 131313137), student_eq));
	Student* p = create_student("Nurse", "Joy", 3, 131313137);
	//Student* o = create_student("George", "Burdell", 65, 902313373);
	printf("TEST CASE 5\nFinding occurence when a node is not in the list should fail: ");
	printf("%d\n\n", find_occurrence(llist, p, student_eq));
	
	free_student(p);
	/* Remember to FREE everything you malloc I malloc'd space for p and now I am done with it so I free it */
	empty_list(llist,free_student);
	
	//emptied list for my test cases
	
	//list of students to use in test cases
	Student* a=(Student*) create_student("Test","A",100,111111);
  	Student* b=(Student*) create_student("Test","B",90,222);
	Student* c=(Student*) create_student("Test","C",99,3);
	Student* d=(Student*) create_student("Test","D",0,0);
	Student* e=(Student*) create_student("Test","E",1,44);

	printf("TEST CASE 6\nShould print list in alphabetical order:\n");
	push_back(llist,a);
	push_back(llist,b);
	push_back(llist,c);
	push_back(llist,d);
	push_back(llist,e);
	traverse(llist,print_student);
	printf("\n");

	

	printf("TEST CASE 7\nSecond student should be gone:\n");
	remove_index(llist,1,free_student);
	traverse(llist,print_student);
	printf("\n");

	printf("TEST CASE 8\nShould return a negative one:");
	printf("%d\n",remove_index(llist,19,free_student));
	printf("\n");
	
	printf("TEST CASE 9\nShould print size of list (4):");
	printf("%d\n",size(llist));
	printf("\n");
	
	printf("TEST CASE 10\nShould print a zero (list is not empty):");
	printf("%d\n",is_empty(llist));
	printf("\n");

	printf("TEST CASE 11A\nShould print last name of last person on the list(E):");
	printf("%s\n",((Student*)back(llist))->last_name);
	printf("\n");
	printf("TEST CASE 11B\nShould print ID of first person on the list(111111):");
	printf("%d\n",((Student*)front(llist))->gtid);
	printf("\n");

	printf("TEST CASE 12\n Prints the third item in the list (index 2):");
	printf("%s\n",((Student*)get_index(llist,2))->last_name);
	printf("\n");

	printf("TEST CASE 13\nPreviously printed student should now be missing:\n");
	remove_index(llist,2,free_student);
	traverse(llist,print_student);
	printf("\n");

  	/* Lets kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 14\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);
 	printf("\n\n"); 	

	printf("TEST CASE 15\nTrying to remove front of empty list:");
	printf("%d\n",remove_front(llist,free_student));
	printf("\n");
 	
	Student* f=(Student*) create_student("Steven","Wojcio",100,902568762);
  	Student* g=(Student*) create_student("Brandon","Whitehead",50,902222222);
	Student* h=(Student*) create_student("Random","Kid",90,902334545);
	

	printf("TEST CASE 16\nPrinting new list:\n");
	push_front(llist,f);
	push_front(llist,g);
	push_front(llist,h);
	traverse(llist, print_student);
	printf("\n");

	printf("TEST CASE 17\nPrints amount of kid's taken out of list (not having a's) and then prints the list:\n");
	printf("%d\n",remove_if(llist,all_A,free_student));
	traverse(llist, print_student);
	printf("\n");
 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */
 	
	printf("TEST CASE 18\nPrinting list missing Steven, after a remove_data call:\n");
	remove_data(llist,f,student_eq,free_student);
	traverse(llist, print_student);
	printf("\n");

	printf("TEST CASE 19\nRemove front of list (size 1):\n");
	printf("%d\n",remove_front(llist,free_student));
	traverse(llist, print_student);
	printf("\n");
	
	printf("TEST CASE 20\nCheck if trying to remove index from an empty list causes an error:\n");
	printf("%d\n",remove_index(llist,0,free_student));
	traverse(llist, print_student);
	printf("\n");


 	/* Testing over clean up*/
	empty_list(llist,free_student);
 	free(llist);
 	
  	return 0;
}
