#include <iostream>

#include "HtmlEditor.h"

int main()
{
    HtmlEditor htmlEditor;
    htmlEditor.Start();

    return 0;
}
/*
insertParagraph end te<>xt'1
insertParagraph end t"ex&t2
insertParagraph end text3
insertImage end 10 10 ../image.jpg
insertImage end 50 50 ../image.jpg
insertImage end 100 100 ../image.jpg
*/