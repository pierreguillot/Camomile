/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_7040746_INCLUDED
#define BINARYDATA_H_7040746_INCLUDED

namespace BinaryData
{
    extern const char*   clear1_png;
    const int            clear1_pngSize = 10453;

    extern const char*   clear2_png;
    const int            clear2_pngSize = 5839;

    extern const char*   copy1_png;
    const int            copy1_pngSize = 5601;

    extern const char*   copy2_png;
    const int            copy2_pngSize = 13753;

    extern const char*   flower1_png;
    const int            flower1_pngSize = 22287;

    extern const char*   flower2_png;
    const int            flower2_pngSize = 3299;

    extern const char*   option_png;
    const int            option_pngSize = 29484;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 7;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
