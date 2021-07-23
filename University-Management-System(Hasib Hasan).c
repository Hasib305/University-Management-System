#include<stdio.h>
#include<string.h>
//admin user : Hasib
//admin pass : 1907089

char gap[50]="____________";

typedef struct admin
{
    char user[100];
    char pass[100];

} admin_info;


typedef struct teacher
{
    char user[100];
    char pass[100];
    char course[100];

} teacher_info;


typedef struct student
{
    char user[100];
    char pass[100];
    char course[100];
    char mark[100];


} student_info;

typedef struct student_cnt //this structure is for counting students
{
    char user[10];
}student_cnt;

void admin_pan();
int admin_check(admin_info );
void teacher_pan();
int teacher_check(teacher_info );
void find_student();
void student_pan();
int student_check(student_info );
void add_teacher();
void update_teacher();
void add_student();
void update_student();
void teacher_do();
void student_do();
void count_student();
void course_assign();
void see_teacher_info();
void see_student_data(student_info );
void insert_mark_if_coursr_found(student_info);
char not[100]="Blank";


void admin_pan() // to call teacher information and student information function
    {
        admin_info a,info;


        fflush(stdin);
        printf("\n Enter Your User Name : ");

        scanf("%s",a.user);
        printf("\n Enter Your Password  : ");
        scanf("%s",a.pass);


        if(admin_check(a)==1) // if the inputed user and pass are matched the function will return 1
        {
            printf("\n\t\t\t~~~~ Welcome To The Admin Panel ~~~~\n");
            printf("\t\t\t------------------------------------\n\n\n");

            printf("\t0.Exit\n\n");
            printf("\t1.Teacher's Information\n\n");
            printf("\t2.Student's Information\n\n");

            printf("\t\t~ Please Select a number from above and press enter ~\n\n");

            int x;
            scanf("%d",&x);
            if (x==1)
            {
                teacher_do();
            }
            else if(x==2)
            {
                student_do();
            }

            else
            {
                return;
            }
        }
   else
        {
            printf("\n\t\tSorry, Invalid User Name or Password. Please try Again ...\n");

        }
    }



    void teacher_do() // this function is for calling Create,update,assign,see teacher's information's function
{

    while(1)
    {
        printf("\n\n\t\t0.Exit\n\n");
        printf("\t\t1.Create Teacher's Information.\n\n");
        printf("\t\t2.Update Teacher's Information.\n\n");
        printf("\t\t3.Assign Course to Teacher. \n\n");
        printf("\t\t4.See Teacher's Assigned Courses.\n\n");
        printf("\n\t\t\t~ Please select a number from above and press enter ~\n\n");

        int x;
        scanf("%d",&x);
        if(x==1)
        {
            add_teacher();
        }
        else if(x==2)
        {
            update_teacher();
        }
        else if(x==3){
            course_assign();

        }
        else if(x==4){
            see_teacher_info();
        }

        else
        {
            return;
        }
    }

}



void add_teacher()  //this function is for creating new teacher's account
{
    teacher_info tch,b;

printf("\n Enter user Name : ");
    fflush(stdin);
    scanf("%[^\n]s",tch.user);
    printf("\n Enter Password  : ");
      fflush(stdin);
    scanf("%[^\n]s",tch.pass);
    printf("\n Enter Course    : ");
     fflush(stdin);
    scanf("%[^\n]s",tch.course);
    FILE *fp;
    fp=fopen("teacher_info.txt","a");
    fwrite(&tch,sizeof(teacher_info),1,fp); //tch structure appended to the teacher_info.txt file
    fclose(fp);
    printf("\n\t\t** Teacher's Account Created Successfully **\n");

}



void update_teacher()  //this function is for updating teacher's user name,password.
{
    char s[100];
    printf("\n Enter Teacher's User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",s);

    FILE *fpp;
    teacher_info b,tch;
    fpp=fopen("teacher_info.txt","r");

    int found=0;

    while((fread(&b,sizeof(teacher_info),1,fpp))>0)// comparing input with the user name inserted in teacher_info file
    {
      if(strcmp(s,b.user)==0 )
        {
            found=1;break;}
    }
    fclose(fpp);

    if(found==1)
    {
printf("\n\t\t ~ Teacher's Account Found ~\n\n");
            printf(" 1.Change User Name\n\n");
            printf(" 2.Change Password \n\n");

            printf("\t\t~ Please select a number from above and press enter\n\n");

            int x;
            scanf("%d",&x);
            if (x==1)
            {
                printf("\n Enter teacher's New User Name : ");
                fflush(stdin);                                     // remove buffer data
                scanf("%[^\n]s",b.user);
            }
            else if(x==2)
            {
                printf(" Enter Teacher's New Password : ");
                fflush(stdin);
                scanf("%[^\n]s",b.pass);
            }
            FILE *fpp,*ftp;
        fpp=fopen("teacher_info.txt","r"); // open teacher_info file
          ftp=fopen("temp_tea.txt","w");   //open temporary file

         while((fread(&tch,sizeof(teacher_info),1,fpp))>0) // read from teacher_info file, updated and inserted to temporary file
        {

            if(strcmp(tch.user,s)==0){ strcpy(tch.user,b.user);strcpy(tch.pass,b.pass);}  //if the user name matched with input  updated input inserted in structure

            fwrite(&tch,sizeof(teacher_info),1,ftp); } // write updated or non updated information from teacher_info file to temporary file

            fclose(fpp);
            fclose(ftp);
        ftp=fopen("temp_tea.txt","r");
fpp=fopen("teacher_info.txt","w");


        while((fread(&b,sizeof(teacher_info),1,ftp))>0) // remove all data from teacher_info file and insert temporary file data to teacher_info file
        {
            fwrite(&b,sizeof(teacher_info),1,fpp);
        }
        fclose(ftp);
        fclose(fpp);
        printf("\n\t\t ~ Teacher's Account Updated Successfully ~\n\n");

    }
    else
    {
        printf("\n\t\t ~ Teacher's Account Not Found ~\n\n");
    }

}



void course_assign(){ // this function is for assigning courses to the teacher
 char s[100];
    printf("\n Enter Teacher's User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",s);

    FILE *fpp,*ftp;
    teacher_info b;
    fpp=fopen("teacher_info.txt","a");
    ftp=fopen("teacher_info.txt","r");
    int found=0;

    while((fread(&b,sizeof(teacher_info),1,ftp))>0) //if the user name found add new course to the teacher
    {
 if(strcmp(s,b.user)==0)
        {
            found=1;
          printf("\n\t\t ~ Teacher's Account Found ~\n\n");

            printf(" Add New Course : ");
fflush(stdin);
            scanf("%[^\n]s",b.course);

             fwrite(&b,sizeof(teacher_info),1,fpp); // append structure with new course

             printf("\n\t\t~ Course Added Successfully ~\n\n");

                       break;

            }
    }
    fclose(fpp);
    fclose(ftp);
    if(found==0){ printf("\n\t\t ~ Teacher's Account Not Found ~\n\n");}
}



void see_teacher_info(){ // To see teacher's assigned courses
char s[100];
    printf("\n Enter Teacher's User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",s);

    FILE *fpp;
    teacher_info b,tch;
    fpp=fopen("teacher_info.txt","r");

    int found=0;

    while((fread(&b,sizeof(teacher_info),1,fpp))>0) //is teacher info found?
    {
      if(strcmp(s,b.user)==0 )
        {
            found=1;break;}
    }
    fclose(fpp);

    if(found==1)
    {
      char d[100]=" Course Name";
      char g[100]=" ________________";
printf("\n\n\t\t%17s\n\t\t%20s\n\n",d,g);
            FILE *fpp,*ftp;
        fpp=fopen("teacher_info.txt","r");

  int i=1;
         while((fread(&tch,sizeof(teacher_info),1,fpp))>0) // search from teacher_info file and print all the courses
        {

            if(strcmp(tch.user,s)==0){ printf("\t\t%d. %-20s\n\n",i++,tch.course);}}

            fclose(fpp);

        }
    else
    {
        printf("\n\t\t ~ Teacher's Account Not Found ~\n\n");
    }

}



void student_do() //this function is for calling creating,updating student account function
{
    while(1)
    {
        printf("\n\t\t\t0.Exit\n\n");
        printf("\t\t\t1.Create Student's Information\n\n");
        printf("\t\t\t2.Update Student's Information\n\n");


        printf("\t\t\t\t~ Please select a number from above and press enter ~\n\n");

        int x;
        scanf("%d",&x);
        if(x==1)
        {
            add_student();
        }
        else if(x==2)
        {
            update_student();
        }

        else return ;
        }
}


void add_student()  //Creating New student account
{
    student_info tch,b;
student_cnt p;

char s[10]="DONE";
    printf("\n\n Enter user Name : ");
    fflush(stdin);
    scanf("%[^\n]s",tch.user);
    printf("\n\n Enter Password  : ");
    scanf("%s",tch.pass);

    strcpy(tch.course,not); // initialize student course and mark with "Blank"
    strcpy(tch.mark,not);
strcpy(p.user,s);
    FILE *fp=fopen("student_info.txt","a");
    FILE *ftp=fopen("student_count.txt","a");
    fwrite(&tch,sizeof(student_info),1,fp);
      fwrite(&p,sizeof(student_cnt),1,ftp);// if a student added insert a random structure in student_cnt file,so further we can count it
    fclose(fp);
    fclose(ftp);

}





void update_student()      //updating student's user name , password
{
   char s[100];
    printf("\n Enter Student's User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",s);

    FILE *fpp;
    student_info b,tch;
    fpp=fopen("student_info.txt","r");

    int found=0;

    while((fread(&b,sizeof(student_info),1,fpp))>0) //check ,student's user name found or not
    {
      if(strcmp(s,b.user)==0 )
        {
            found=1;break;}
    }
    fclose(fpp);

    if(found==1)
    {
printf("\n\n\t\t\t~~ Student Account Found ~~\n\n");
            printf(" 1.Change User Name\n\n");
            printf(" 2.Change Password \n\n");

            printf("\n\t\t~ Please select a number from above and press enter ~\n\n");

            int x;
            scanf("%d",&x);
            if (x==1)
            {
                printf("\n Enter Student's New User Name : ");
                fflush(stdin);
                scanf("%[^\n]s",b.user);
            }
            else if(x==2)
            {
                printf("\n Enter Student's New Password : ");
                fflush(stdin);
                scanf("%[^\n]s",b.pass);
            }
            FILE *fpp,*ftp;
        fpp=fopen("student_info.txt","r");
          ftp=fopen("temp_stu.txt","w");

         while((fread(&tch,sizeof(student_info),1,fpp))>0)  // read from student_info file ,updated and inserted to temporary file
        {

            if(strcmp(tch.user,s)==0){ strcpy(tch.user,b.user);strcpy(tch.pass,b.pass);} //if the user name matched with input  updated input inserted in structure


            fwrite(&tch,sizeof(student_info),1,ftp);} // write updated or non updated information from student_info file to temporary file


            fclose(fpp);
            fclose(ftp);
        ftp=fopen("temp_stu.txt","r");
fpp=fopen("student_info.txt","w");


        while((fread(&b,sizeof(student_info),1,ftp))>0) // remove all data from student_info file and insert temporary file data to student_info file
        {
            fwrite(&b,sizeof(student_info),1,fpp);
        }
        fclose(ftp);
        fclose(fpp);
        printf("\n\n\t\t\t~ Student's Information Updated Successfully ~\n\n");
    }
    else
    {
        printf("\n\n\t\t~ Sorry Student's Account Not Found ~\n\n");
    }

}



  void teacher_pan() //to call the function for finding student,providing marks,showing the number of students
    {
        teacher_info tch;

printf("\n Enter User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",tch.user);
printf("\n Enter Password  : ");
    scanf("%s",tch.pass);

if(teacher_check(tch)==1) //is teacher's account found
        {
            printf("\n\n\t\t\t\t~~~ Welcome To The Teacher Panel ~~~\n\n");
            while(1){
        printf("\n\n \t0.Exit\n");
        printf("\n \t1.Find a Student\n");
        printf("\n \t2.Provide Class-Test Marks\n");
        printf("\n \t3.The Number Of Students\n\n");

         printf("\t\t ~ Please select a number from above and press enter ~\n\n");

        int x;
        scanf("%d",&x);
        if(x==1)
        {
            find_student();}
        else if(x==2)
        {
            find_student();
        }
        else if(x==3)
        {
            count_student();
        }

        else return;
}
}
        else {printf("\n\n\t\t\t~~ Sorry Teacher's Account Not Found ~~\n\n");}
}



void find_student()        //for finding student from the student file and providing mark to the student
{
student_info tch;

printf("\n Enter Student's User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",tch.user);

     int found=0;
    student_info b;
    FILE *fpp;
    fpp=fopen("student_info.txt","r");
    while(fread(&b,sizeof(student_info),1,fpp)) // find a student from student_info file
    {

        if(strcmp(b.user,tch.user)==0)
        {
            found=1;
               printf("\n\n\t\t\t ~~ %s's Account Found ~~\n\n",tch.user);

                 see_student_data(tch);   //go to the see_student_data() function


               printf("\n\n\t\t\t~ Do You Want To Provide Mark? ~\n\n");
               printf(" 1.YES\n\n");
                printf(" 2.NO\n\n");

                printf("\t~ Please select a number from above and press enter~\n\n");

                int x;
        scanf("%d",&x);

        if(x==1)
        {
            printf("\n Insert Course Name: ");
    fflush(stdin);
    scanf("%[^\n]s",b.course);
            printf("\n Insert Mark       : ");
    fflush(stdin);
    scanf("%[^\n]s",b.mark);


     FILE *fp;
     fp=fopen("student_info.txt","a");
     fwrite(&b,sizeof(student_info),1,fp); //oped student file in append mode and add course  and mark with new structure
     fclose(fp);
     printf("\n\n\t\t\t ~~ Mark Inserted Successfully ~~\n\n");
}
        else{printf("\n\n\t\t\t~~ Thank You ~~");return;}

        break;

        }
    }

    if(found==0){printf("\n\n\t\t~~ Student's Account Not Found ~~\n");}
}

void count_student()  //counting total number of student

{

int found=0;
    student_cnt b;
    FILE *fpp;
    fpp=fopen("student_count.txt","r");
    while(fread(&b,sizeof(b),1,fpp)) //counting total number of student from student_count file
    {
        found++;

    }
    printf("\n\n\t\t\t*** Total Number of Student is %d ***\n\n",found);

}


void student_pan()  // for login and calling the function to see marks
    {
        student_info tch;
printf("\n Enter Your User Name : ");
    fflush(stdin);
    scanf("%[^\n]s",tch.user);
    printf("\n Enter Your Password : ");
    scanf("%s",tch.pass);


        if(student_check(tch)==1) // is the student information found?
        {
            printf("\n\n\t\t\t~~~ Welcome To The Student Panel ~~~\n\n\n");
        printf("\t\t0.Exit\n\n");
        printf("\t\t1.Check Class-Test Marks\n\n");

         printf("\t\t\t~ Please select a number from above and press enter ~\n\n\n");

        int x;
        scanf("%d",&x);
        if(x==1)
        {
            see_student_data(tch); // see student marks in different courses
        }

        else return ;
}
        else {printf("\n\n\t\t\t~~ Sorry Student's Account Not Found ~~");}

    }

void see_student_data(student_info stc){ // to see student marks in different courses

char n[50]="Srudent Name";
        char c[50]=" Course Name";
             char m[50]="Marks";

FILE *fpp;
            student_info b;
                fpp=fopen("student_info.txt","r");
                     printf("%15s",n);
                     printf("%15s",c);
                     printf("%15s\n",m);
                     printf("%15s%15s%15s\n\n",gap,gap,gap);
                while((fread(&b,sizeof(student_info),1,fpp))>0){    //if student's user name found print the course name and mark from structure
                        if(strcmp(stc.user,b.user)==0 ){

                    printf("%15s",b.user);
                    printf("%15s",b.course);
                    printf("%15s\n\n",b.mark);}
                }

fclose(fpp);
}



int admin_check(admin_info a) //checking is if the inputed user name and password valid for admin ?
{

    int found=0;
    admin_info b;
    FILE *fpp;
    fpp=fopen("admin_info.txt","r");
    (fread(&b,sizeof(admin_info),1,fpp));

    if(strcmp(b.user,a.user)==0 && strcmp(b.pass,a.pass)==0) //is inputed user and pass matched with information in file
    {
        found=1;
    }
    else
    {
        found=0;
    }
return found;

}

int teacher_check(teacher_info a) //checking is if the inputed user name and password valid for teacher?
{

    int found=0;
    teacher_info b;
    FILE *fpp;
    fpp=fopen("teacher_info.txt","r");
    while(fread(&b,sizeof(teacher_info),1,fpp))
    {

        if(strcmp(b.user,a.user)==0 && strcmp(b.pass,a.pass)==0) //is inputed user and pass matched with information in file
        {
            found=1;
        }
}
    return found;
}

int student_check(student_info a) //checking is if the inputed user name and password valid for student?
{
int found=0;
    student_info b;
    FILE *fpp;
    fpp=fopen("student_info.txt","r");
    while(fread(&b,sizeof(student_info),1,fpp))
    {

        if(strcmp(b.user,a.user)==0 && strcmp(b.pass,a.pass)==0) //is inputed user and pass matched with information in file
        {found=1;}
}
    return found;
}


  int main()
    {

     FILE *fp;
    fp=fopen("admin_info.txt","w");
    admin_info a={"Hasib","1907089"};

    fwrite(&a,sizeof(admin_info),1,fp); // write user name and password in admin_info file
    fclose(fp);

        printf("\t\t\t**** WELCOME TO UNIVERSITY MANAGEMENT SYSTEM ****\n");
        printf("\t\t\t_________________________________________________\n\n\n");
        while(1){                                                                   //when exit is called back to front page
        printf("\n\n\t\t\t~~~ Please select a number from bellow and press enter ~~~\n\n");
        printf("\t\t0.Exit\n\n");
        printf("\t\t1.Admin Panel\n\n");
        printf("\t\t2.Teacher Panel\n\n");
        printf("\t\t3.Student Panel\n\n");

        int pan;
        scanf("%d",&pan);

        if(pan==1)
        {
            admin_pan();
        }
        else if(pan==2)
        {
            teacher_pan();
        }

        else if(pan==3)
        {
            student_pan();
        }
        else
        {
                return 0;}
        }
}
