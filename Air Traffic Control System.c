#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20

int heap_size = 0;
const int INF = 100000;
int fid[20];
int flights[20];

struct land
{
	int id;
	float fuel;
	int wait_time;
	float distance;
	char name[30];
	int p;
};

struct depart
{
	int id;
	char name[30];
	int hh,mm,ss;
	char dir[15];
	int p;
};	

void swap( int *a, int *b ) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

//function to get right child of a node of a tree
int get_right_child(int A[], int index) {
  if((((2*index)+1) < MAX) && (index >= 1))
    return (2*index)+1;
  return -1;
}

//function to get left child of a node of a tree
int get_left_child(int A[], int index) {
    if(((2*index) < MAX) && (index >= 1))
        return 2*index;
    return -1;
}

//function to get the parent of a node of a tree
int get_parent(int A[], int index) {
  if ((index > 1) && (index < MAX)) {
    return index/2;
  }
  return -1;
}

void max_heapify(int A[], int index) {
  int left_child_index = get_left_child(A, index);
  int right_child_index = get_right_child(A, index);

  int largest = index;

  if ((left_child_index <= heap_size) && (left_child_index>0)) {
    if (A[left_child_index] > A[largest]) {
      largest = left_child_index;
    }
  }

  if ((right_child_index <= heap_size && (right_child_index>0))) {
    if (A[right_child_index] > A[largest]) {
      largest = right_child_index;
    }
  }

  if (largest != index) {
    swap(&A[index], &A[largest]);
    max_heapify(A, largest);
  }
}

int extract_max(int A[]) {
  int maxm = A[1];
  A[1] = A[heap_size];
  heap_size--; 
  max_heapify(A, 1);
  return maxm;
}

void increase_key(int A[], int index, int key) {
  A[index] = key;
  while((index>1) && (A[get_parent(A, index)] < A[index])) {
    swap(&A[index], &A[get_parent(A, index)]);
    index = get_parent(A, index);
  }
}

void insert(int A[], int key) {
  heap_size++;
  A[heap_size] = -1*INF;
  increase_key(A, heap_size, key);
}

void print_heap(int A[]) {
  int i;
  for(i=1; i<=heap_size; i++) {
    printf("%d\n",A[i]);
  }
  printf("\n");
}

int main()
{
	struct land *l=(struct land*)malloc(sizeof(struct land));
	int s,ch2,ch3,n=0,i=0,j=0;
	struct depart *d=(struct depart*)malloc(sizeof(struct depart));
	int c,t=0;
	char ch1;
	do
	{
	printf("Enter your choice(l->Landing,t->TakeOff):");
	scanf(" %c",&ch1);
	switch(ch1)
	{
		case 'l':
		{
		printf("Landing flights\n");
		printf("---------------\n");
		do
		{	
		printf("0->Exit\n1->Get landing flight details\n2->Displaying landing flight details\n3->Writing into a file\n4->Reading from the file\n5->Priority chart\n6->Pririty calculation\n7->Displaying flight details with priority\n8->Order flights based on priority\n9->Runway gate and hangar allotment\nEnter your choice(0-9):");
		scanf("%d",&ch2);
		switch(ch2)
		{
		case 1://getting the details of landing flights
			{
				do
				{
				printf("--------------------------------------------------\n");
				printf("Enter flight details regarding landing:\n");
				printf("--------------------------------------------------\n");
				printf("Enter the flight id:");
				scanf("%d",&l[n].id);
				printf("Enter thr flight name:");
				scanf("%s",l[n].name);
				printf("Enter the distance from runway(in km):");
				scanf("%f",&l[n].distance);
				printf("Enter the fuel remaining(in ltrs):");
				scanf("%f",&l[n].fuel);
				printf("Enter the waiting time in halt(in min):");
				scanf("%d",&l[n].wait_time);
				n++;
				l=realloc(l,(n+1)*sizeof(struct land));
				printf("Enter 0 to stop getting inputs:");
				scanf("%d",&s);	
				printf("\n");
				}while(s!=0);
				break;
			}
		case 2://printing the details of landing flights
			{
				i=0;
				printf("--------------------------------------------------\n");
				while(i<n)
				{
					printf("Airplane %d\n",i+1);
					printf("-----------\n");
					printf("Flight Id    :%d\n",l[i].id);
					printf("Flight Name  :%s\n",l[i].name);
					printf("Distance     :%f\n",l[i].distance);
					printf("Fuel left    :%f\n",l[i].fuel);
					printf("Waiting time :%d\n",l[i].wait_time);
					i++;
					printf("--------------------------------------------------\n");
				}
				break;
			}
		case 3://writing the details into a file named land.txt
			{
				FILE *of;
				struct land k;
				of = fopen("land.txt","w");
				fwrite(l, sizeof(struct land),n,of);
				printf("--------------------------------------------------\n");
				printf("Landing flight details were written successfully\n");
				printf("--------------------------------------------------\n");
				fclose(of);
				break;
			}
		case 4://reading the file named land.txt
			{
				FILE *of;
				struct land k;
				of = fopen("land.txt","r");
				printf("--------------------------------------------------------------------\n");
				printf("Flight ID  Flight Name  Distance from runway   Fuel left   Time halt\n");
				printf("--------------------------------------------------------------------\n");
				while(1)
				{
				fread(&k, sizeof(struct land),1,of);
				if(feof(of))
				break;
				printf("%d\t   %s\t\t%f\t%f\t%d\n",k.id,k.name,k.distance,k.fuel,k.wait_time);
				}
				printf("\n");
				fclose(of);
				break;
			}
		case 5:
			{
				//priority chart 
				printf("\n\t\t\tPriority chart\n");
				printf("\t\t\t--------------\n\n");
				printf("------------------------------------------------------------\n");
				printf("|     Paramaters             |  low   |  medium  |   high   |\n");
				printf("|-----------------------------------------------------------|\n");
				printf("|                            | (0-5)  |  (5-8)   |  (8-20)  |\n");
				printf("|Distance from runway(in km) |   20   |    10    |     5    |\n");
				printf("|-----------------------------------------------------------|\n");
				printf("|                            | (0-40) |  (40-80) | (80-150) |\n");
				printf("|Fuel left (in litres)       |   30   |    20    |    10    |\n");
				printf("|-----------------------------------------------------------|\n");
				printf("|                            | (20-50)|  (10-20) |  (0-10)  |\n");
				printf("|Time halt (in minutes)      |    2   |     5    |    10    |\n");
				printf("------------------------------------------------------------\n\n");
				break;
			}
		case 6://priority calculation
			{
				i=0;
				printf("--------------------------------------------------------------\n");
				printf("Displaying landing flight details after priority calculation\n");
				printf("--------------------------------------------------------------\n");
				printf("Flight No.   Flight ID  Priority value\n");
				printf("--------------------------------------------------------------\n");
				while(i<n)
				{
					int p1,p2,p3;
					if(l[i].distance<5)
					p1=20;
					else if(l[i].distance<8)
					p1=10;
					else
					p1=5;
					if(l[i].fuel<40)
					p2=30;
					else if(l[i].fuel<80)
					p2=20;
					else
					p2=10;
					if(l[i].wait_time>20)
					p3=10;
					else if(l[i].wait_time>10)
					p3=5;
					else
					p3=2;
					l[i].p=p1+p2+p3;
					printf("Flight %d \t%d \t  %d\n",i+1,l[i].id,l[i].p);
					i++;
				}
				printf("--------------------------------------------------------------\n");
				break;
			}
		case 7://inserting elements into a priority queue and ordering them based on priority
			{
				int a[n];
				i=0;
				while(i<n)
					{
						insert(a,l[i].p);
						i++;
					}
				printf("--------------------------------------------------------------\n");
				printf("Ordering of landing flights based on the priority being calculated\n");
				printf("--------------------------------------------------------------\n");
				i=0;
				printf("Flight No.  Flight ID    Name   Priority value\n");
				printf("--------------------------------------------------------------\n");
				while(i<n)
					{
						int m=extract_max(a);
						int j=0;
						while(j<n)
						{
							if(m==l[j].p)
							{
							printf("%d\t     %d\t  %s\t %d\n",i+1,l[j].id,l[j].name,m);
							break;
							}
							j++;
						}
						i++;
					}
				printf("--------------------------------------------------------------\n");
				break;
			}
		case 8://writing flight details according to priority
			{
				FILE *fp;
				fp = fopen("landpriority.txt", "w");
				int b[n];
				i=0;
				while(i<n)
					{
						insert(b,l[i].p);
						i++;
					}
				i=0;
				printf("--------------------------------------------------------------\n");
				fprintf(fp,"Flight No.  Flight ID    Name   Priority value\n");
				while(i<n)
					{
						int m=extract_max(b);
						int j=0;
						while(j<n)
						{
							if(m==l[j].p)
							{
							fprintf(fp,"%d\t%d\t%s\t%d\n",i+1,l[j].id,l[j].name,l[j].p);
							flights[i]=l[j].id;
							break;
							}
							j++;
						}
						i++;
					}
				printf("Written the landing flight details into file named landpriority\n");
				printf("--------------------------------------------------------------\n");
				fclose(fp);
				break;
			}
		case 9://runway,gate and hanger alottment
			{				
				int o,r,g;
				printf("--------------------------------------------------------------\n");				
				printf("Enter number of runways available:");
				scanf("%d",&r);
				printf("Enter number of gates available:");
				scanf("%d",&g);
				int G[g],R[r],H[n];
				printf("--------------------------------------------------------------\n");
				printf("Runway gate and hangar allotment\n");
				printf("--------------------------------------------------------------\n");
				for(i=0;i<g;i++)
				{
					G[i]=0;
				}
				for(i=0;i<r;i++)
				{
					R[i]=0;
				}
				for(i=0;i<n;i++)
				{
					for(o=0;o<r;o++)
					{
						for(j=0;j<g;j++)
						{
							if(i%r==o)
							{
								if(R[o]!=0)
								{
									if(G[i%g]!=0)
									{
										H[i]=G[i%g];
										printf("Flight id %d is sent to hangar\n",G[i%g]);
										printf("-----------------------------------------------\n");;
										
									}
									G[i%g]=R[o];
									printf("Flight id %d is sent to gate no. %d\n",G[i%g],(i%g)+1);	
									printf("-----------------------------------------------\n");	
								}
								R[o]=flights[i];
								printf("Flight id %d is sent to runway no. %d\n",R[o],o+1);
								printf("-----------------------------------------------\n");
								break;
							}
						}
					}
				}
				printf("--------------------------------------------------------------\n");
				break;
			}
		case 0:
			break;
		}
	}while(ch2!=0);
	break;
	}
	case 't':
		{
			printf("Takeoff flights\n");
			printf("---------------\n");
			do
			{
			printf("0->Exit\n1->Get takeoff flight details\n2->Displaying takeoff flight details\n3->Writing into a file\n4->Reading from the file\n5->Pririty calculation\n6->Displaying flight details with priority\n7->Order flights based on priority\n8->Runway gate allotment and takeoff order\nEnter your choice(0-8):");
			scanf("%d",&ch3);
			switch(ch3)
			{
			case 1:
				{
					do
					{
					printf("--------------------------------------------------\n");
					printf("Enter flight details regarding take off:\n");
					printf("--------------------------------------------------\n");
					printf("Enter the flight id:");
					scanf("%d",&d[t].id);
					printf("Enter thr flight name:");
					scanf("%s",d[t].name);
					printf("Enter the departure time(HH:MM:SS):");
					scanf("%02d:%02d:%02d",&d[t].hh,&d[t].mm,&d[t].ss);
					printf("Enter the direction of take off(1-south,2-north,3-east,4-west,5-northeast,6-northwest,7-southeat,8-southwest):");
					scanf("%s",d[t].dir);
					t++;
					d=realloc(d,(t+1)*sizeof(struct depart));
					printf("Enter 0 to stop getting inputs:");
					scanf("%d",&c);	
					}while(c!=0);
					break;
				}
			case 2://printing details regarding departure
				{	
				i=0;				
					printf("---------------------------------------\n");
					while(i<t)
					{
						printf("Airplane %d\n",i+1);
						printf("-----------\n");
						printf("Id             : %d\n",d[i].id);
						printf("Name           : %s\n",d[i].name);
						printf("Departure time : %d:%d:%d\n",d[i].hh,d[i].mm,d[i].ss);
						printf("Direction      : %s\n",d[i].dir);
						i++;
						printf("---------------------------------------\n");
					}
					break;
				}
			case 3://writing the details into a file named depart.txt
				{
					FILE *od;
					struct depart q;
					od = fopen("depart.txt","w");
					fwrite(d, sizeof(struct depart),t,od);
					printf("--------------------------------------------------\n");
					printf("Flight take off details were written successfully\n");
					printf("--------------------------------------------------\n");
					fclose(od);
					break;
				}
			case 4://reading the file named depart.txt
				{
					FILE *od;
					struct depart q;
					od = fopen("depart.txt","r");
					printf("--------------------------------------------------------------\n");
					printf("Flight ID  Flight Name  Departure time   Direction of takeoff\n");
					printf("--------------------------------------------------------------\n");
					while(1)
					{
					fread(&q, sizeof(struct depart),1,od);
					if(feof(od))
					break;
					printf("%d\t  %s\t%d:%d:%d\t\t%s\n",q.id,q.name,q.hh,q.mm,q.ss,q.dir);
					}
					printf("--------------------------------------------------------------\n");
					fclose(od);	
					break;
				}
			case 5://priority calculation based on departure time
			{
				i=0;
				printf("--------------------------------------------------------------\n");
				printf("Displaying flight takeoff details after priority calculation\n");
				printf("--------------------------------------------------------------\n");
				printf("Flight No.   Flight ID  Priority value\n");
				printf("--------------------------------------------------------------\n");
				while(i<t)
				{
					int p1;
					d[i].p=(d[i].hh*3600)+(d[i].mm*60)+d[i].ss;
					printf("Flight %d \t%d \t%d\n",i+1,d[i].id,d[i].p);
					i++;
				}
				printf("--------------------------------------------------------------\n");
				break;
			}
			case 6:	//inserting into priority queue
				{
					int arr[t];
					i=0;
					while(i<t)
						{
							insert(arr,d[i].p);
							i++;
						}
					int planes[t];					
					//flight is ordered based on priority					
					i=0;
					int array2[t];
					while(i<t)
						{
							int m=extract_max(arr);
							planes[i]=m;
							i++;
						}
					for (i = t - 1, j = 0; i >= 0; i--,j++)
				      array2[j] = planes[i];
				    for (i = 0; i < t; i++)
				    {
				      planes[i] = array2[i];
				    }		
					printf("--------------------------------------------------------------\n");			  
				    printf("Ordering of takeoff flights based on the priority being calculated\n");
					printf("--------------------------------------------------------------\n");					
					printf("Flight No.  Flight ID    Name   Priority value\n");
					printf("--------------------------------------------------------------\n");
					i=0;
					while(i<t)
						{
							int j=0;
							while(j<t)
							{
								if(planes[i]==d[j].p)
								{
								printf("%d\t   %d\t %s\t%d\n",i+1,d[j].id,d[j].name,d[j].p);
								break;
								}
								j++;
							}
							i++;
						}
					printf("--------------------------------------------------------------\n");					
					break;
				}
			case 7:	//writing takeoff flight details according to priority
				{
					FILE *fdp;
					fdp = fopen("departpriority.txt", "w");
					int barr[t];
					i=0;
					while(i<t)
						{
							insert(barr,d[i].p);
							i++;
						}
					int planes1[t];						
					//flight is ordered based on priority					
					i=0;
					int array1[t];
					while(i<t)
						{
							int m=extract_max(barr);
							planes1[i]=m;
							i++;
						}
					for (i = t - 1, j = 0; i >= 0; i--,j++)
				      array1[j] = planes1[i];
				    // Copying reversed array into the original
				    for (i = 0; i < t; i++)
				    {
				      planes1[i] = array1[i];
				  	}				  
					i=0;
					printf("--------------------------------------------------------------\n");
					fprintf(fdp,"Flight No.  Flight ID    Name   Priority value\n");
					while(i<t)
						{
							int j=0;
							while(j<t)
							{
								if(planes1[i]==d[j].p)
								{
								fprintf(fdp,"%d\t%d\t%s\t%d\n",i+1,d[j].id,d[j].name,d[j].p);
								fid[i]=d[j].id;
								break;
								}
								j++;
							}
							i++;
						}
					printf("Written the takeoff flight details into file named departpriority\n");
					printf("--------------------------------------------------------------\n");
					fclose(fdp);
					break;
				}
			case 8://runway,gate allotment and takeoff order
				{	
					int o,r,g;
					int T[t];
					printf("Enter number of runways available:");
					scanf("%d",&r);
					printf("Enter number of gates available:");
					scanf("%d",&g);
					int G[g],R[r];
					printf("--------------------------------------------------------------\n");
					printf("Runway,gate allotment and take off order\n");
					printf("--------------------------------------------------------------\n");
					for(i=0;i<r;i++)
					{
						R[i]=0;
					}
					for(i=0;i<g;i++)
					{
						G[i]=0;
					}
					for(i=0;i<t;i++)
					{
						for(o=0;o<g;o++)
						{
							for(j=0;j<r;j++)
							{
								if(i%g==o)
								{
									if(G[o]!=0)
									{
										if(R[i%r]!=0)
										{
											T[i]=R[i%r];
											printf("Flight id %d is taken off\n",R[i%r]);
											printf("-----------------------------------------------------\n");
										}
										R[i%r]=G[o];
										printf("Flight id %d is sent to runway no. %d\n",R[i%r],(i%r)+1);
										printf("-----------------------------------------------------\n");		
									}
									G[o]=fid[i];
									printf("Flight id %d is sent to gate no. %d\n",G[o],o+1);
									printf("-----------------------------------------------------\n");
									break;
								}
							}
						}
					}
					printf("--------------------------------------------------------------\n");	
					break;
				}
			case 0:
				break;	
			}	
			}while(ch3!=0);
			break;
		}
	case 'e':
		exit(0);
	}
	} 
	while(ch1!='e');
	return 0;
}

