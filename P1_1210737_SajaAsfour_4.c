#include <stdio.h>
#include <stdlib.h>
//saja nazih hassan asfour
//1210737
//sec 4
typedef struct SajaNode* PtrNode;//set a new name to SajaNode* to use it for node
typedef struct SajaNode* LinkList;//set a new name to SajaNode* to use it for List
typedef struct Node* singleList;
LinkList MakeList(int x);
int Find(int x,singleList L);
void Delete(int x,LinkList L);
void InsertAtLast(PtrNode *L,int x);
void InsertAtFirst(PtrNode *L,int x);
void PrintList(LinkList L);
void DeleteList(LinkList L);
int Size(LinkList L);
int CompereTheNumbers(PtrNode n1,PtrNode n2);
LinkList Addition(LinkList number1,LinkList number2);
LinkList Subtraction(LinkList number1,LinkList number2);
LinkList Multiplication(LinkList number1,LinkList number2);
void PrintSingle(singleList node);
void Reverse(LinkList * L);
void singleInsert(singleList * L,int x);
LinkList Division(LinkList Dividend,LinkList Divisor);
struct Node{
    struct Node *next;
    int data;
};
struct SajaNode {
    int Element;
    struct SajaNode * Next;
    struct SajaNode *Pre;
};
int main()
{
   int choice;
   LinkList number1=NULL;//double linked list to hold the first number
   LinkList number2=NULL;// double linked list to hold the second number
   LinkList res=NULL;    //double linked list to hold the result
   LinkList remainder=NULL; //double linked  list to hold the remainder
   singleList head =NULL;//linked list
   do{//menu:
    printf("Enter your choice:\n");
    printf("1. Read numbers from a file\n");
    printf("2. Add numbers\n");
    printf("3. Subtract numbers\n");
    printf("4. Multiply numbers\n");
    printf("5. Divide numbers\n");
    printf("6. Print result to a file\n");
    printf("7. Exit\n");
    scanf("%d", &choice);
        switch(choice){
            case 1:;FILE *in=fopen("input.txt","r");//this is to read from file and print and let user choice
                    if(in==NULL){
                    printf("ERROR , can not open the file!\n");
                    }
                     int val=0,x, data;//val is the number of large integer in the file
                     while (fscanf(in, "%d", &data) != EOF) {// Read integers from the file until the end is reached
                        singleInsert (&head, data); // Insert the integer into the linked list
                        val++;// Increment the count of integers
                     }
                    fclose(in);
                    printf("The file has been read \n\n");
                    int first,sec;
                    PrintSingle(head);
                    printf("\n");
                    int valid=0;// Flag variable
                    while(!valid){//keep in this loop until valid=0
                        printf("PlEASE CHOOSE TWO NUMBERS FROM 1 TO %d\n",(val));
                        scanf("%d %d",&first,&sec);
                        if((first<=(val)&&first>0) && (sec<=(val)&&sec>0)){//if the user enter two number from the correct range
                            valid=1;// !valid=0 so we left the loop
                        }

                        else{//if the user select an number out of the range
                            printf("PlEASE CHOOSE TWO NUMBERS FROM 1 TO %d... \n",(val));
                        }
                    }
                    int s=Find(first,head);
                    int num=s;
                    int digit;
                    while(num>0){
                        digit=num%10;
                        InsertAtLast(&number1,digit);
                        num=num/10;
                    }
                     x=Find(sec,head);
                    num=x;
                    while(num>0){
                        digit=num%10;
                        InsertAtLast(&number2,digit);
                        num=num/10;
                    }
                break;
            case 2://this case is for addition
                if (number1 == NULL || number2 == NULL) {
                    printf("Please read numbers from a file first.\n");
                    }
                    else {
                    res = Addition(number1, number2);
                    PrintList(res);
                    printf("\nAddition complete.\n");
                }
                break;
            case 3:if (number1 == NULL || number2 == NULL) {
                    printf("Please read numbers from a file first.\n");
                    }
                    else {
                    res = Subtraction(number1, number2);
                    PrintList(res);
                    printf("Subtraction complete.\n");
                    }
                break;
            case 4: if (number1 == NULL || number2 == NULL) {
                    printf("Please read numbers from a file first.\n");
                    }
                    else {
                    res = Multiplication(number1, number2);
                    PrintList(res);
                    printf("Multiplication complete.\n");
                    }
                break;
            case 5:
                if (number1 == NULL || number2 == NULL) {
                    printf("Please read numbers from a file first.\n");
                } else {
                   //res=Division(number1,number2);
                    printf("Division complete.\n");
                }
                break;
            case 6:;
                    //PrintList(res);
                  if (res  == NULL) {
                    printf("No result to write.\n");
                 } else {
                    FILE * out=fopen("output.txt","w");
                    while(res!=NULL){
                        fprintf(out,"%d",res->Element);
                        res=res->Next;
                    }

                    printf("Result written to file.\n");
                    fclose(out);
                }

                break;
            case 7:
                printf("Exiting program.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
         printf("\n");
   }while(choice!=7);
   //to free the memory
   DeleteList(number1);
   DeleteList(number2);
   DeleteList(res);
   DeleteList(remainder);

    return 0;
}
LinkList MakeList(int x){//this is to crate an node and put data in it
   LinkList L=(PtrNode)malloc(sizeof(struct  SajaNode));
    if(L==NULL){
        printf("Out of the memory!\n");
        exit(0);
    }
    L->Element=x;
    L->Next=NULL;
    L->Pre=NULL;
    return  L;
}
int Find(int x,singleList L){//this use to find an element in linked list and return it
    singleList temp=L;// Assign the head of the linked list to a temporary variable
    int val=1,data=0;/*val is a Counter for the current position in the list
    and data is Variable to store the data of the found element*/
    while(temp->next!=NULL ){ // Traverse the linked list until the end is reached
        if(val==x){// Check if the current position matches the desired position
            data=temp->data;// Assign the data of the element at the desired position
            return data;// Return the data of the found element
        }
        else{
            temp=temp->next;// Move to the next node in the linked list
            val++;//Increment the position counter
        }
    }
    return -1;// If the desired position is not found, return -1
}
void Delete(int x,LinkList L){//function to delete the an node have element x of the linked list
    PtrNode temp=L->Next;
    while(temp!=NULL && temp->Element!=x)
        temp=temp->Next;
    if(temp!=NULL){
        if(temp->Pre!=NULL)
            temp->Pre->Next=temp->Next;
        if(temp->Next!=NULL)
            temp->Next->Pre=temp->Pre;
        free(temp);
    }
}
void PrintSingle(singleList node){//this for print the single linked list
    singleList temp=node;
    int count=1;//to hold the number of large integer in file
    while(temp!=NULL){
        printf("%d  > %d \n",count++,temp->data);
        temp=temp->next;
    } printf("\n");
}
void InsertAtLast(PtrNode *L,int x){//insert the element in last node
    PtrNode temp= MakeList(x);
    //if there is no node in the linked list,make the temp node  the head
    if(*L==NULL){
        *L=temp;
        temp->Pre=NULL;
        return;//*
    }
    PtrNode tmp=*L;
    // Traverse to the end of the list
    while(tmp->Next!=NULL)
        tmp=tmp->Next;
    //insert the new node at the end of the list
    tmp->Next=temp;
    temp->Pre=temp;
}
void InsertAtFirst(PtrNode *L,int x){//insert an element in the first node of double linked list
    LinkList node= MakeList(x);//make a new linked list
    if(*L==NULL){
        *L=node;
    }
    else{
        node->Next=*L;
        (*L)->Pre=node;//*L make error without()
        *L=node;
    }
}
//function to reverse a given doubly linked list
void Reverse(LinkList * L){
    LinkList p=NULL;
    LinkList head=*L;
    while(head!=NULL){//swap to the next and previous for all nodes
        p=head->Pre;
        head->Pre=head->Next;
        head->Next=p;
        head=head->Pre;
    }
    if(p!=NULL){
        *L=p->Pre;
    }
}
void PrintList(LinkList L){//this is to print the double linked list
      PtrNode temp=L;
      if(L==NULL){//if there is no nodes in the linked list
        printf("Empty List!");
        return;
    }
    else{
        while(temp!=NULL){// Traverse to the end of the list and print the element in each node
            printf("%d",temp->Element);
            temp=temp->Next;
        }
    }printf("\n");
}
void DeleteList(LinkList L){//to Delete the double linked list
    LinkList temp1=L;
    LinkList temp2=L->Next;
    while (temp2!=NULL){
        free(temp1);
        temp1=temp2;
        temp2=temp2->Next;
    }
    free(temp1);//to delete node by node
}
int Size(LinkList L){
    int size=0;
    LinkList temp=L;
    while (temp->Next!=NULL){
        size++;
        temp=temp->Next;
    }
    return size;
}
//this function is to add two large integer as doubly linked list
LinkList Addition(LinkList number1,LinkList number2){
    LinkList res=NULL;
    PtrNode temp;
    int carry=0,sum;
    int digit1,digit2;
    //Base case if both lists are empty and carry=0
    if(number1==NULL &&number2==NULL && carry==0)
        return NULL;
    // Traverse both lists until at least one list is empty
    while (number1!=NULL || number2!=NULL ) {
        digit1=((number1!=NULL)?number1->Element:0);//this for the digit in number1
        digit2=((number2!=NULL)?number2->Element:0);//this for the digit in number2
        //calculate the sum
        sum=carry+digit1+digit2;
        // Calculate the carry value
        carry=sum/10;
        sum=sum%10;// Take the modulo 10 of the sum to get the actual digit value
        // Create a new node for the sum digit
        temp=(LinkList)malloc(sizeof(struct SajaNode));
        temp->Element=sum;
        temp->Next=NULL;
        InsertAtLast(&res,sum);
        // Move to the next nodes in both numbers(linked list)
        if(number1)
            number1=number1->Next;
        if(number2)
            number2=number2->Next;
    }
    // If there is a remaining carry, create a new node for it
        if(carry>0){
            InsertAtLast(&res,carry);
    }
      //  Reverse(&res);

    return res;
}
//this function is to subtract 2 large integer as doubly linked list:
LinkList Subtraction(LinkList number1,LinkList number2){//number1-number2
   LinkList res=NULL;
    int borrow=0;
    int sub;
    int digit1,digit2;
    //compare the number to know if the result have a negative sign
    int x=CompereTheNumbers(number1,number2);
    if(x<0){//if x=-1
       PtrNode temp=number1;
       number1=number2;
       number2=temp;
     //  printf("-");
    }
       // Traverse both lists until at least one list is empty
       while (number1 != NULL || number2 != NULL) {
           // Calculate the subtraction of the two number
           digit1 = ((number1 != NULL) ? number1->Element : 0);
           digit2 = ((number2 != NULL) ? number2->Element : 0);
           digit1 -= borrow;
           borrow = 0;
           sub = digit1 - digit2;
           // Calculate the borrow value
           if (sub < 0) {
               borrow = 1;
               sub += 10;
           }
           InsertAtLast(&res, sub);
           // Move to the next nodes (next digit)in both lists(numbers)
           if (number1)
               number1 = number1->Next;
           if (number2)
               number2 = number2->Next;
       }
    while(res->Next!=NULL &&res->Element==0){
        PtrNode RemoveZero=res;
        res=res->Next;
        res->Pre=NULL;
        free(RemoveZero);
    }
    return  res;
}
int CompereTheNumbers(PtrNode n1,PtrNode n2){
    // Traverse number1 to reach the last element
    while (n1 != NULL && n1->Next != NULL) {
        n1 = n1->Next;
    }
    // Traverse number to reach the last element
    while (n2 != NULL && n2->Next != NULL) {
        n2 = n2->Next;
    }
    // Compare the data of the last elements
    if (n1 == NULL && n2 == NULL) {
        return 0;  // Both n are empty
    } else if (n1 == NULL) {
        return -1; // n1 is empty, n2 is not empty
    } else if (n2 == NULL) {
        return 1;  // n2 is empty, n1 is not empty
    } else {
        // Compare the data of the last elements
        if (n1->Element > n2->Element) {
            return 1;  // n1 last element is greater
        } else if (n1->Element < n2->Element) {
            return -1; // n2 last element is greater
        } else {
            return 0;  // Both n elements are equal
        }
    }
}
// multiplication function
LinkList Multiplication(LinkList number1, LinkList number2){
    LinkList res=NULL;// Resultant linked list to store the multiplication result
    int counterforlevel =0;// Counter to add zeros equal to each level
    int counterforzero =0 ;// Counter to keep track of zeros to add
    PtrNode temp2=number2;// Pointer to traverse number2
    int i;// Counter for iterations
    // Outer loop to traverse number2
    while (temp2!=NULL){
        PtrNode temp1=number1;// Pointer to traverse number1
        PtrNode tempRes=NULL;// Temporary linked list to store intermediate results
        int carry=0;// Variable to store the carry during multiplication
         //Inner loop to multiply each digit of number1 with the current digit of number2
        for (i=0;i<1;i++){// Only one iteration to multiply all digits of number1
            while(temp1!=NULL){ // Traverse number1 and perform multiplication
                int mul=(temp1->Element * temp2->Element)+carry; // Multiply current digits and add carry
                carry=mul/10;// Update carry
                mul%=10;// Get the remainder as the current digit of the result
                InsertAtLast(&tempRes,mul);// Insert the current digit to the temporary result linked list
                temp1=temp1->Next;// Move to the next digit in number1
            }
            // If there is a carry after multiplying all digits of number1, add it to the result
            if(carry>0)
                InsertAtLast(&tempRes,carry);
            // Add zeros at the beginning based on the level
            if (counterforlevel>0)
            {
                while (counterforzero!=0)
                {
                    InsertAtFirst(&tempRes,0);
                    counterforzero--;
                }

            }
            // Perform addition of the temporary result with the overall result
            res= Addition(res,tempRes);
            counterforlevel++;// Increment the level counter
            // Update the counter for zeros to add
            counterforzero= counterforlevel ;
        }
        // Reset the counter for iterations
        i=0;
        // Move to the next digit in number2
        temp2=temp2->Next;
        // Reset the temporary result linked list
        tempRes=NULL;
    }
    // Return the final result of multiplication
    return res;
}
void singleInsert(singleList * L,int x){//to insert at the first of single linked list
    singleList  node=(singleList )malloc(sizeof(struct Node));
    if(node==NULL){
        printf("out of the memory\n");
        exit(0);
    }
    node->data=x;//put the element of the linked list equal to x
    node->next=*L;
    *L=node;
}
/*LinkList Division(LinkList Dividend,LinkList Divisor){
    LinkList  quotient = NULL ,temp1 = Dividend,remainder = NULL;
    // Check for zero divisor
    if (Divisor->Element == 0 && Divisor->Next == NULL) {
        printf("Error: can not Division by zero.\n");
        return NULL;
    }
    // Check if dividend is negative
    int isNegative = (Dividend->Element < 0);

    // Check if divisor is negative
    int DivisorNegative = (Dividend->Element < 0);
    // Ignore sign for division
    temp1->Element= abs(temp1->Element);
    Divisor->Element = abs(Divisor->Element);

    // Perform division
    while (temp1 != NULL) {
        int Data = temp1->Element;
        int quotientValue = 0;
        // Add the next digit to the current value
        while (remainder != NULL && CompereTheNumbers(remainder, Divisor)) {
            InsertAtFirst(&remainder, 0);
            Data = Data * 10 + remainder->Element;
            quotientValue *= 10;
        }
        // Calculate the quotient value
        while (CompereTheNumbers(MakeList(Data), Divisor)) {
            Data -= Divisor->Element;
            quotientValue++;
        }
        // Add the quotient value to the quotient list
        InsertAtFirst(&quotient, quotientValue);

        // Update the remainder
        remainder = MakeList(Data);
         // Move to the next digit
        temp1 = temp1->Next;
    }
    // Remove leading zeros in the quotient
    while (quotient->Next != NULL && quotient->Element == 0) {
        PtrNode temp = quotient;
        quotient = quotient->Next;
        quotient->Pre = NULL;
        free(temp);
    }
    // Apply the sign to the quotient
    if (isNegative)
        quotient->Element = -(quotient->Element);
        // Restore the signs of the dividend and divisor
    Dividend->Element = (isNegative) ? -(Dividend->Element) : Dividend->Element;
    Divisor->Element = (DivisorNegative) ? -(Divisor->Element) : Divisor->Element;

    return quotient;

}*/
