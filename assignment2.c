#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main() 
{
    int n;
    //input the max #
    scanf("%d", &n);
    char line[10000];
    //char line2[10000];
    fgets(line, 10000, stdin); // remove the new line character
    
    int midpoint;
    int max = n;
    int min = 1;
    int prevGuess;
    //used for prevGUess
    int buffer;
    int guess;
    //# of guesses it should take before game over
    int guesses = 1 + (2 * log2(n));
    int range;
    
    //this loops through the max # of tries
    for(int i = 1; i < guesses; i++)
    {
        //distance the value is in
        range = (max - min);
        
        //if it's not the first iteration
        if(i != 1)
        {
            //if the user enters "Yes" or "Game Over", return 0
            if (line[0] == 'Y' || line[0] == 'G')
            {
                return 0;
            }
            
            //if the range we are checking in is less than 3
            if(range < 3)
            {
                //guess min + 1
                min = min + 1;
                printf("%d\n", min);
            }
            
            //calculating and printing the midpoint
            midpoint = (min + max)/2;
            printf("%d\n", midpoint);
            fflush(stdout);
            prevGuess = midpoint;
            
            //scanning in the line
            fgets(line, 10000, stdin);
            //if yes, return 0
            if (line[0] == 'Y' || line[0] == 'G')
            {
                return 0;
            }
            //if no, check to see what is after the no
            else
            {
                //print one less than the midpoint
                buffer = midpoint;
                midpoint -= 1;
                printf("%d\n", midpoint);
                fflush(stdout);
                prevGuess = buffer;
                
                //scan in the line
                fgets(line, 10000, stdin);
                
                //if yes or game over, return 0
                if (line[0] == 'Y' || line[0] == 'G')
                {
                    return 0;
                }

                //if its warmer, the max becomes one more than the midpoint
                if(line[4]=='W')
                {
                    max = midpoint + 1;
                }
                //if its colder, the min becomes one more than the midpoint
                else if(line[4]=='C')
                {
                    min = midpoint + 1;
                }
                //if theres no change, print half of previous and current guess
                else if(line[4]=='N')
                {
                    buffer = midpoint;
                    guess = (midpoint + prevGuess)/2;
                    printf("%d\n", guess);
                    fflush(stdout);
                    prevGuess = buffer;
                }
            }
        }
        
        //for the first iteration
        if(i==1)
        {
            //the midpoint is half the min and the max
            midpoint = (min + max)/2;
            printf("%d\n", midpoint);
            fflush(stdout);
            prevGuess = midpoint;
            
            //scan in the line
            fgets(line, 10000, stdin);
            
            //if yes or game over, return 0
            if (line[0] == 'Y' || line[0] == 'G')
            {
                return 0;
            }
            
            //if no
            else
            {
                //print out the midpoint - 1
                buffer = midpoint;
                midpoint -= 1;
                printf("%d\n", midpoint);
                fflush(stdout);
                prevGuess=buffer;
                
                //scan in next line
                fgets(line, 10000, stdin);
                //if it's yes or game over, return 0
                if (line[0] == 'Y' || line[0] == 'G')
                {
                    return 0;
                }
                
                //if it's warmer, the new max is the midpoint + 1
                if(line[4]=='W')
                {
                    max = midpoint + 1;
                }
                //if colder, the new min is the midpoint + 1
                else if(line[4]=='C')
                {
                    min = midpoint + 1;
                }
        
                //if theres no change, print half of the midpoint and previous guess
                else if(line[4] == 'N')
                {
                    buffer = midpoint;
                    guess = (midpoint + prevGuess)/2;
                    printf("%d\n", guess);
                    fflush(stdout);
                    prevGuess = buffer;
                }
            }
        }
    }
    return 0;
}
