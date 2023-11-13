#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])  {
    if (argc > 4) {
        printf("More than 4 arguments. Please write '-help' for instructions\n");
    }
    else if (argc == 4 && strstr(argv[1], ".csv") && strcmp(".csv", strstr(argv[1], ".csv")) == 0 && strstr(argv[2], ".xml") && strcmp(".xml", strstr(argv[2], ".xml")) == 0
    && strcmp("-opsys", argv[3]) == 0 && (strcmp("1", argv[4]) == 0 || strcmp("2", argv[4]) == 0 || strcmp("3", argv[4]) == 0)) {
        // There are two pointers, fpr for reading and fpw for writing
        FILE *fRead, *fWrite;
        // .csv file for reading
        fRead = fopen(argv[1], "r");
        // .xml file for writing
        fWrite = fopen(argv[2], "w");

        // Helps to make Strings
        char string[999999];

        // ERROR: Opening File
        if (fRead == NULL) {
            puts("ERROR: Source File");
            exit(1);
        }
        // ERROR: Opening File
        else if (fWrite = NULL) {
            puts("ERROR: Destination File");
            exit(1);
        }
        // Program starts if there is no error to openning files
        else {
            // Saves number of the row
            int row = 0;
            char* root = strtok(argv[1], ".");
            fprintf(fWrite, "<%s>\n", root);
 
            // Starts to process all lines in the file
            while (fgets(string, 999998, fRead)) {
                // This variable will be the end of the line in each OS
                char* oneLine;
                // For Windows
                if (strcmp(argv[4], "1") == 0)
                    oneLine = strtok(string, "\r\n");
                // For Linux
                else if (strcmp(argv[4], "2") == 0)
                    oneLine = strtok(string, "\n");
                // For MacOS
                else if (strcmp(argv[4], "3") == 0)
                    oneLine = strtok(string, "\r");

                char* token;
                // Keeps strings without token part
                char* notToken = oneLine;
                // Keeps seperator in a variable which is "seperator"
                const char* separator = ",";
                int firstSep = 0;
                int lastSep = 0;
                // Checks the first character of the line if there is any seperator there
                int checkSepBegin = 0;
                if (oneLine[0] == separator[0])
                    checkSepBegin = 1;
                
                char firstLine[999][999];
                int whileCount = 0;
                // Takes the first line
                // Because first line is not the data. It shows us what data is in this element.
                // So we can use first line is an sample.
                if (row == 0) {
                    while ((token = strtok_r(notToken, separator, &notToken))) {
                        // Lowercase
                        for(int i = 0; token[i]; i++){
                            token[i] = tolower(token[i]);
                        }

                        // Changes "Space ( )" character with "Underscore (_)"
                        int i = 0;
                        while (token[i] != '\0') {
                            if (token[i] == ' ')
                                token[i] = '_';
                            i++;
                        }
                        strcpy(firstLine[whileCount], token);
                        whileCount++;
                    }
                    whileCount = 0;
                }
                // If it is "NOT" the first line
                // It means now we will take our "DATA"
                else {
                    fprintf(fWrite, "\t<row id=\"%d\">\n", row);

                    // Splits every elements by "seperator"
                    while ((token = strtok_r(notToken, separator, &notToken))) {
                        // Checks the first character for the seperator
                        if (whileCount == 0 && firstSep == 1) {
                            fprintf(fWrite, "\t\t<%s/>\n", firstLine[whileCount]);
                            firstSep = 0;
                            whileCount++;
                        }
                        // Checks the last character for the seperator
                        if (whileCount == 0 && notToken[strlen(notToken) - 1] == separator[0])
                            lastSep = 1;
                        
                        fprintf(fWrite, "\t\t<%s>%s</%s>\n", firstLine[whileCount], token, firstLine[whileCount]);
                        if (notToken[0] == separator[0]) {
                            whileCount++;
                            fprintf(fWrite, "\t\t<%s/>\n", firstLine[whileCount]);
                        }
                        whileCount++;
                    }
                    // ERROR: Last character is seperator
                    // If there is a  "seperator" at the end of the line, changes it to an empty character
                    if(lastSep == 1){
                        fprintf(fWrite, "\t\t<%s/>\n", firstLine[whileCount]);
                        lastSep = 0;
                    }
                    whileCount = 0;
                    // Row is finished
                    fprintf(fWrite, "\t</row>\n");
                }
                row ++;
            }
            // Root is closed
            fprintf(fWrite, "</%s>", root);
        }
        // Operations are closed
        fclose(fRead);
        fclose(fWrite);
        printf("Succesfully converted from csv to xml !\n");
    }
    else {
        int checkHelp = 0;
        for (int i = 1; i < argc; i++)
        {
            if (strcmp("-help", argv[i]) == 0)
            {   // Print the instructions for this program
                printf("1. In the first argument define the csv file name you want to use\n");
                printf("2. In the second argument define the xml file name you want to create\n");
                printf("3. To define the end of line character format, use '-opsys' argument and define the number of the opsys\n");
                printf(" 1 - Windows\n 2 - Linux\n 3 - MacOS\n\n");
                printf("Anytime you need help, just add an -help argument\n");
                checkHelp = 1;
                break;
            }
        }
        if (checkHelp == 0)
            printf("You have entered arguments improper way. Please enter properly. To get help add -h argument\n");
    }
    return 0;   
}