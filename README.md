MobiWriter
==========

Minimal writer for the mobipocket format. No images or other fancy stuff like TOC supported.

I use this for all my kindle books, because MobiWriter enables me to directly specify the raw html contents of the mobi file. Tools like KindleGen, calibre, etc. add specific formatting nonsense to the html source, that sucks.

####Usage (requires basic html, no css etc.):

```c++
#include <iostream>
#include <fstream>
#include "MobiWriter.h"

int main(int argc, const char * argv[]) {
    MobiBook *mobi_book = new MobiBook("Hello Book Title", "Hello Book Author");
    mobi_book->addHtmlFile("source.html");
    
    
    MobiWriter *mobi_writer = new MobiWriter();
    mobi_writer->write(mobi_book, "Hello_Book_Title.mobi");
}
```
