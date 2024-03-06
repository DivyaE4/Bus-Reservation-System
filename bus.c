#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

typedef struct BinarySearchTree
{
  int userId; // busNo0SeatNo. // passenger number to traverse through the tree
  char name[10];
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
}BST;


BST *root = NULL;
int cost(BST *r);              // calculates costs
void status();                 // shows bus and seats status
void busLists();               // shows buslist and do booking seat and return user ID
void displaySeat(int bus[33]); // Display the seats of buses
void cancel(int x,int reservationDate);            //cancel the booking 
BST *reservationInfo(BST *, int, int *); // Display Reservation Info
BST *insert(BST **r, int custID); // inserting a node 
int isBooked(int choice,int seatNumber); // to find if the seat is booked or not
BST* minValueNode(BST* node); // finds leftmost node
BST* deleteNode(BST* root, int key); // deletes a node


int busSeat[32][9] = {0}; //it means 9 buses and 32 seats in each bus have been initialised to 0

BST *reservationInfo(BST *r, int s, int *custIDmatched) // find function, s is customer id that the user inputs
//the customer id is passed as input and if it is valid cusid matched is changed to 1
// and traverse through the tree till userId is matched and then once it matched everything is printed
{
  if (r == NULL)
    return NULL;
  BST *presentnode = r;
  while (presentnode)
  {
   

    if (presentnode->userId == s)
    {
      *custIDmatched = 1;
      if (busSeat[presentnode->userId / 1000][presentnode->userId % 100] == 0)
        {
          printf("\nThis reservation has been canceled.\n");
          return NULL; // Returning NULL as the reservation is canceled
        }
     
      printf("\n-----------------------------------------------------------------");
      printf("\n||              NAME: %10s                               ||", (presentnode->name));
      printf("\n||              USER ID: %d                              ||", presentnode->userId);
      printf("\n||              BUS NUMBER: %d                                  ||", (presentnode->userId) / 1000);
      printf("\n||              SEAT NUMBER: %d                                 ||", (presentnode->userId) % 100);
      printf("\n||              TICKET COST: Rs.%d                             ||", cost(presentnode));
      printf("\n-----------------------------------------------------------------");
     
      getch();
      return r;
    }
    else if (presentnode->userId > s) // if s is less than passno move left
      presentnode = presentnode->left; 
    else
      presentnode = presentnode->right; //if s is more than passno move right
  }

  return NULL;
}
BST *insert(BST **r, int custId) // insert into a bst using user id as the reference
{
  if (*r == NULL)
  {

    *r = (BST *)malloc(sizeof(BST));
    (*r)->userId = custId;
    if (*r == NULL)
    {
      printf("No memory…");
      return NULL;
    }
    else
    {
      (*r)->left = (*r)->right = NULL;
      printf("\n   ENTER THE PERSON NAME: ");
      scanf("%s", &((*r)->name));
    }
  }
  else
  {
    if ((*r)->userId > custId)
    {
      (*r)->left = insert(&((*r)->left), custId);
    }
    else if ((*r)->userId < custId)
    {
      (*r)->right = insert(&((*r)->right), custId);
    }
  }
  return *r;
}

void displaySeat(int bus[33])
{
  for (int i = 1; i <= 32; i++)
  {
    
    if (i < 10 && i > 0)
    {
      printf("0%d .", i);
    }
    else
    {
      printf("%d .", i);
    }

    
    {
      if (bus[i] == 0)
        printf("EMPTY ");
      else
        printf("BOOKED"); 
    }
    printf("         ");
    if (i % 4 == 0)
      printf("\n");
  }
}

int cost(BST *r)
{
  int cost, buscost;
  buscost = (r->userId) / 1000;
  switch (buscost % 3)
  {
  case 1:
    return 1000;
    break;
  case 2:
    return 800;
    break;
  case 0:
    return 500;
    break;
  default:
    return 0;
    break;
  }
}

void busLists() // 9 buses list
{
  
  printf("-------------------------------------------------------------------------------------------------------");
  printf("\nBus.No\t Bus Name\t\t\tDestinations  \t\t\tCharges  \t\tTime\n");
  printf("-------------------------------------------------------------------------------------------------------");
  
  printf("\n1\tVolvo A/C Multi Axle          \tBengaluru to Chennai       \tRs.1000   \t\t07:00  AM");
  printf("\n2\tGaruda Plus                    \tHyderabad to Vijayawada       \tRs.800    \t\t01:30  PM");
  printf("\n3\tSarige   \t\t\tBangalore to Mysore \t\tRs.500    \t\t03:50  PM");
  printf("\n4\tSuper Deluxe         \t\tPokhara To Benigha    \t\tRs.1000    \t\t01:00  AM");
  printf("\n5\tKaveri Express     \t\tBangalore to Tirupati \t\tRs.800    \t\t12:05  AM");
  printf("\n6\tNeelgiri Express     \t\tCoimbatore to Ooty    \t\tRs.500   \t\t09:30  AM");
  printf("\n7\tDakshin Express       \t\tChennai to Kanyakumari         \tRs.1000   \t\t11:00  PM");
  printf("\n8\tGanga Yatra       \t\tVaranasi to Haridwar     \tRs.800    \t\t08:15  AM");
  printf("\n9\tSleeper Class        \t\tChennai to Coimbatore      \tRs.500    \t\t04:00  PM");
  printf("\n");
  printf("\n   PRESS 'ENTER' KEY TO CONTINUE ");
  getch();
}

void status()
{
  int busNum;
  busLists();
busInput:
  printf("\n\nENTER YOUR BUS NUMBER : ");
  scanf("%d", &busNum);
  if (busNum <= 0 || busNum >= 10)
  {
    
    printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
    
    goto busInput;
  }
  printf("\n");
  displaySeat(busSeat[busNum]);
  getch();
}

BST* minValueNode(BST* node) {
    BST* current = node;

    // Traverse the tree to find the leftmost leaf node
    while (current && current->left != NULL)
        current = current->left;

    return current;
}


BST* deleteNode(BST* root, int key) {
    if (root == NULL) return root;

    if (key < root->userId)
        root->left = deleteNode(root->left, key);
    else if (key > root->userId)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            BST* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BST* temp = root->left;
            free(root);
            return temp;
        }
        BST* temp = minValueNode(root->right);
        root->userId = temp->userId;
        root->right = deleteNode(root->right, temp->userId);
    }
    return root;
}

void cancel(int randomNum,int reservationDate) // randomNum is the reservation number that the user inputs
{
  int reservationNo;
  int seatNumber;
  int choice;
  char c;
  int seatCancel;

  time_t current_time;
  struct tm *time_info;

  current_time = time(NULL);

  time_info = localtime(&current_time);

  int  cancelationDate=time_info->tm_mday;

aa:
{
  printf("\nENTER YOUR RESERVATION NUMBER : ");
  scanf("%d", &reservationNo);
  if (reservationNo == randomNum)
  {
    printf("\nDO YOU WANT TO CONTINUE ? %d \nENTER (Y/N) : ", reservationNo);
    scanf("%s", &c);
    if (c == 'y' || c == 'Y')
    {
      printf("\n\n============================================\n\n");
      printf("   ENTER THE BUS NUMBER: ");
      scanf("%d", &choice);

      printf("\n HOW MANY SEATS DO WANT TO CANCEL : ");
      scanf("%d", &seatCancel);
      for (int i = 0; i < seatCancel; i++)
      {
        printf("   \nENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);

        busSeat[choice][seatNumber] = 0;
      }
      
      root = deleteNode(root, reservationNo);
      
      printf("\n\nYOUR RESERVATION HAS BEEN CANCELLED !!\n\n");
      if(reservationDate+5>=cancelationDate)
      {
        printf("Half the money will be refunded");
      }
      else{
        printf("No refund available cause exceeded date for refund");
      }
      printf("\n  PRESS 'ENTER' KEY TO CONTINUE \n");
      getch();
      displaySeat(busSeat[choice]);
    }

    else if (c == 'n' || c == 'N')
    {
      printf("\nYOUR RESERVATION CANCELATION HAS BEEN DENIED\n");
    }
  }
  else
  {
    printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
    goto aa;
  }
}
}



int main()
{
  srand(time(0));
  int randomNum = rand();
  int num, i, custID, reservationNo;
  BST *root1;
  
main:
{
  do
  {
    printf("\n\n====================================================================\n\n");
    printf("\t\t\t\tBUS RESERVATION\t\t");
    printf("\n\n=====================================================================\n");
    printf("\n====================");
    //;
    printf("  MAIN MENU ");
    //
    printf("=====================\n\n");
    printf("    1 VIEW BUS LIST \n\n");
    printf("    2 BOOK TICKETS\n\n");
    printf("    3 CANCEL BOOKING\n\n");
    printf("    4 BUSES SEATS INFO\n\n");
    printf("    5 RESERVATION INFO\n\n");
    printf("    6 EXIT\n");
    printf("\n=====================================================\n");
    printf("\n   ENTER YOUR CHOICE: ");
    scanf("%d", &num);
    switch (num)
    {
    case 1:
      busLists(); // for list of bus
      break;
    case 2:
      
      busLists(); // for booking the tickets

      int CustId, choice, seats;

    busChoice:
      printf("\n\nCHOOSE YOUR BUS  : ");
      scanf("%d", &choice);
      if (choice <= 0 || choice > 9)
      {
        
        printf("\nENTER VALID BUS NUMBER !! \n");
        
        getch();
        goto busChoice;
      }
      printf("\n");
      displaySeat(busSeat[choice]);
    busSeatChoice:
      printf("\n\nNO. OF SEATS YOU NEED TO BOOK : ");
      scanf("%d", &seats);
      if (seats <= 0)
      {
        
        printf("\nENTER VALID SEAT NUMBER!!\n");
        
        goto busSeatChoice;
      }
      else if (seats > 32)
      {
        
        printf("\nENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n");
        
        goto busSeatChoice;
      }
      int seatNumber;
      for (int i = 1; i <= seats; i++)
      {
        printf("\n\n==================================================================================\n\n");
      seat:
        printf("   ENTER THE SEAT NUMBER: ");
        scanf("%d", &seatNumber);
        
        if (seatNumber <= 0)
        {
          ////;
          printf("\n   ENTER VALID SEAT NUMBER!!\n\n");
          ////
          goto seat;
        }
        else if (seatNumber > 32)
        {
          ////;
          printf("\n   ENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n\n");
          ////
          goto seat;
        }
        else 
        {
          if(isBooked(choice,seatNumber))
          {
          printf("SEAT IS ALREADY BOOKED PLEASE CHOOSE ANOTHER SEAT \n!!");
          goto seat;
          }
        }
        
        CustId = choice * 1000 + seatNumber; // CustumerId choice is the bus no chosen so when the custId is divided
        // by 1000 u get the bus no again
        busSeat[choice][seatNumber] = 1;
        root = insert(&root, CustId);
        printf("\n   YOUR CUSTOMER ID IS : %d", CustId);
        //
        printf("\n\n==================================================================================\n\n");
      }
      printf("\nYOUR RESERVATION NUMBER IS : ");
      //;
        time_t current_time;
        struct tm *time_info;

        current_time = time(NULL);

        time_info = localtime(&current_time);
      int reservationDate=time_info->tm_mday;
      printf("%d\n", randomNum);
      printf("\nPLEASE NOTE DOWN YOUR RESERVATION NUMBER FOR CANCEL BOOKING TICKETS!!\n");
      //
      printf("PRESS 'ENTER' KEY TO CONTINUE ");
      getch();
      break;

    case 3:
      cancel(randomNum,reservationDate);
      break;
    case 4:
      status(randomNum);
      break;
    case 5:
    takingReservationNo:
      printf("\n   ENTER YOUR RESERVATION NUMBER :");
      scanf("%d", &reservationNo);

      if (randomNum == reservationNo)
      {
      cust:
        printf("\n   ENTER YOUR CUSTOMER ID :");
        scanf("%d", &custID);
        int custIDmatched = 0;
        root1 = reservationInfo(root, custID, &custIDmatched);
        if (custIDmatched == 0)
        {
          
          printf("\n   ENTER CORRECT CUSTOMER ID!!\n");
          
          goto cust;
        }
      }
      else
      {
        
        printf("\n INVALID RESERVATION NUMBER PLEASE ENTER CORRECT RESERVATION NUMBER !!\n");
        
        goto takingReservationNo;
      }
      break;
    default:
      //;
      printf("\n\n   INVALID INPUT CHOOSE CORRECT OPTION\n");
      //
      break; 
    }
  } while (num != 6);
  printf("\n\n=====================================================================\n\n");
  printf("THANK YOU FOR USING THIS BUS RESERVATION SYSTEM");
  printf("\n\nPRESS ANY KEY TO EXIT THE END PROGRAM !! \n");
  printf("\n\n");
  getch();
  return 0;
}
}
int isBooked(int choice,int seatNumber)
        {
          if(busSeat[choice][seatNumber]==1)
            return 1;
          else
            return 0;
        }