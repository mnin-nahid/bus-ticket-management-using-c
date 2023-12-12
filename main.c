#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    long int id;
    char name[30];
    long int phone;
    int ticket_type;
}ticket;

//Functions
void printBanner();
void display_main_menu();
void book_ticket();
void take_input(ticket *p);
void display_my_ticket(int find_id);
void passenger_list(int pass);
void start_this_bus(int pass);
void view_my_history(int find_id);

int main(){
    int selection;
    int find_id;
    int admin_pass;
    while (1)
    {
        printBanner();
        display_main_menu();
        printf("\033[0;34m");
        printf("Set> ");
        printf("\033[0m");
        scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            system("clear");
            printBanner();
            book_ticket();
            getchar();
            getchar();
            break;
        
        case 2:
            system("clear");
            printBanner();
            printf("Enter your id : ");
            scanf("%ld", &find_id);
            display_my_ticket(find_id);
            getchar();
            getchar();
            break;
        case 3:
            system("clear");
            printf("Enter your id : ");
            scanf("%d", &find_id);
            view_my_history(find_id);
            getchar();
            getchar();
            break;
        case 4:
            system("clear");
            printBanner();
            printf("Enter admin password :");
            scanf("%d", &admin_pass);
            passenger_list(admin_pass);
            getchar();
            getchar();
            break;
        case 5:
            system("clear");
            printBanner();
            printf("Enter admin password :");
            scanf("%d", &admin_pass);
            start_this_bus(admin_pass);
            getchar();
            getchar();
            break;
        case 9:
            system("clear");
            printBanner();
            printf("Thanks for using our service!\n");
            getchar();
            getchar();
            exit(1);
            break;
        default:
            break;
        }
    }
    
    
    return 0;
}

void printBanner(){ //Defination of print Banner
        printf("\033[0;32m");
        printf("##########################################################\n");
        printf("#########|--------------------------------------|#########\n");
        printf("#########|    Wellcome to Bus Ticket Counter    |#########\n");
        printf("#########|--------------------------------------|#########\n");
        printf("##########################################################\n");
        printf("\033[0;0m");
}
void display_main_menu(){ //Defination of display_main_menu
    printf("| Please select from the following options: |\n");
    printf("[1] Book a ticket\n");
    printf("[2] View my tickets\n");
    printf("[3] View my travel history\n");
    printf("[4] Pessenger List (Admin Only)\n");
    printf("[5] Start BUS (Admin Only)\n");

    printf("\033[0;31m");
    printf("[9] Exit\n\n");
    printf("\033[0m");
}

void book_ticket(){       
    FILE *fp;
    fp = fopen("ticket_db", "a");
    if(fp == NULL){
        printf("DB is not found\n");
        printf("To continue press any key!\n");
        return;
    }
    else{
        ticket p;
        take_input(&p);
        fprintf(fp,"%ld,%s,%ld,%d\n", p.id,p.name,p.phone,p.ticket_type);
        fclose(fp);
        printf("Ticket Buy Successfull\n");
        printf("To continue press any key!");
    }
}
void take_input(ticket *p){
    printf("[1] City campus > Permenant campus\n");
    printf("[2] Permenant campus > City campus\n");
    printf("[3] Kuril > Permenant campus\n");
    printf("[4] Permenant campus > Kuril\n");
    printf("Enter id : ");
    scanf("%ld", &p->id);

    printf("Enter name : ");
    scanf("%s", p->name);

    printf("Enter mobile Number : ");
    scanf("%ld", &p->phone);

    printf("Which ticket you want to buy : ");
    scanf("%d", &p->ticket_type);

}
void display_my_ticket(int find_id){
    FILE *fp;
    fp = fopen("ticket_db", "r");
    if(fp == NULL){
        printf("empty!\n");
        printf("To continue press any key!\n");
        return;
    }
    else{
        ticket p;
        int read = 0;
        int records = 0;
        int flag;
        ticket all_ticket[25];
        do
        {
            read = fscanf(fp,
                          "%ld,%29[^,],%ld,%d\n",
                          &all_ticket[records].id,
                          all_ticket[records].name,
                          &all_ticket[records].phone,
                          &all_ticket[records].ticket_type
                          );

            if(read == 4) records++;
            if(read != 4 && !feof(fp)){
                printf("File formated incorrect!\n");
            }
            if(ferror(fp)){
                printf("Error reading file!\n");
            }
        } while (!feof(fp));
        fclose(fp);
        for(int i = 0; i < records; i++){
            
            if(all_ticket[i].id == find_id){
                flag = i;
            }
        }
        printf("id - %ld, name - %s, phone - %ld, ticket type - %d\n",
                all_ticket[flag].id,
                all_ticket[flag].name,
                all_ticket[flag].phone,
                all_ticket[flag].ticket_type);
        printf("\nTo continue press any key!\n");
        
    }
}

void passenger_list(int addmin_pass){
    if(addmin_pass == 4206){
        FILE *fp;
        fp = fopen("ticket_db", "r");
        if(fp == NULL){
            printf("DB is not found\n");
            printf("To continue press any key!\n");
            return;
        }
        ticket passengers[25];
        int read = 0;
        int records = 0;
        do
        {
            read = fscanf(fp,
                          "%ld,%29[^,],%ld,%d\n",
                          &passengers[records].id,
                          passengers[records].name,
                          &passengers[records].phone,
                          &passengers[records].ticket_type);

            if(read == 4) records++;
            if(read != 4 && !feof(fp)){
                printf("File formated incorrect!\n");
            }
            if(ferror(fp)){
                printf("Error reading file!\n");
            }
        } while (!feof(fp));
        fclose(fp);

        printf("Total :%d Passengers\n\n", records);
        for(int i = 0; i < records; i++){
            printf("id - %ld, name - %s, phone - %ld, ticket type - %d\n",
                    passengers[i].id,
                    passengers[i].name,
                    passengers[i].phone,
                    passengers[i].ticket_type);
        }
    }
    else{
        printf("Wrong! password.");
    }
    printf("Press any key to go back\n");
}

void start_this_bus(int admin_pass){
    if(admin_pass == 4206){
        FILE *fp, *history;
        fp = fopen("ticket_db", "r");
        if(fp == NULL){
            printf("DB is not found\n");
            printf("To continue press any key!\n");
            return;
        }
        history = fopen("p_history_db", "a");
        if(history == NULL){
            printf("DB is not found\n");
            printf("To continue press any key!\n");
            return;
        }
        int read = 0;
        int records = 0;
        ticket passengers[25];
        do
        {
            read = fscanf(fp,
                          "%ld,%29[^,],%ld,%d\n",
                          &passengers[records].id,
                          passengers[records].name,
                          &passengers[records].phone,
                          &passengers[records].ticket_type);

            if(read == 4) records++;
            if(read != 4 && !feof(fp)){
                printf("File formated incorrect!\n");
            }
            if(ferror(fp)){
                printf("Error reading file!\n");
            }
        } while (!feof(fp));
        fclose(fp);
        for(int i = 0; i < records; i++){

            fprintf(history,"%ld,%s,%ld,%d\n",
                            passengers[i].id,
                            passengers[i].name,
                            passengers[i].phone,
                            passengers[i].ticket_type);
        }
        fclose(history);
        remove("ticket_db");
        printf("Bus started.\n");
        printf("New bus ticket avable now.\n");
        printf("Press Enter again.\n");

    }
    
}

void view_my_history(int find_id){
    system("clear");
    FILE *fp;
    fp = fopen("p_history_db", "r");
    if(fp == NULL){
        printf("empty!\n");
        printf("To continue press any key!\n");
        return;
    }
    else{
        ticket p;
        printBanner();
        int read = 0;
        int records = 0;
        ticket all_ticket[25];
        do
        {
            read = fscanf(fp,
                          "%ld,%29[^,],%ld,%d\n",
                          &all_ticket[records].id,
                          all_ticket[records].name,
                          &all_ticket[records].phone,
                          &all_ticket[records].ticket_type
                          );

            if(read == 4) records++;
            if(read != 4 && !feof(fp)){
                printf("File formated incorrect!\n");
            }
            if(ferror(fp)){
                printf("Error reading file!\n");
            }
        } while (!feof(fp));
        fclose(fp);
        for(int i = 0; i < records; i++){
            
            if(all_ticket[i].id == find_id){
                printf("id - %ld, name - %s, phone - %ld, ticket type - %d\n",
                all_ticket[i].id,
                all_ticket[i].name,
                all_ticket[i].phone,
                all_ticket[i].ticket_type);
            }
        }
        
        printf("\nTo continue press any key!\n");
        
    }
}