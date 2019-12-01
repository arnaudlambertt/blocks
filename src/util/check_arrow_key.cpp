/** \brief renvoie un nombre par paramètre en fonction de la touche appuyée
 *
 * \param val int*
 * \return
 *
 */

#include "check_arrow_key.h"

void CheckArrowKey (int &val)
{
int key;
    key = getch();
    if (key == 224) { //arrowkey
            key = getch();
            switch (key) {
            case 72:    //up
                val = 1;
                break;
            case 75:    //left
                val = 2;
                break;
            case 77:    //right
                val = 3;
                break;
            case 80:    //down
                val = 4 ;
                break;
            }
        }
    else if  (key == 8) //backspace
    val = 10;
    else if (key == 13) //enter
    val = 5;
    else if(key == 27) //esc
    val = 6;
    else
    val = 0;
}
