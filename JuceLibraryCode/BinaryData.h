/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_24019154_INCLUDED
#define BINARYDATA_H_24019154_INCLUDED

namespace BinaryData
{
    extern const char*   clear0_png;
    const int            clear0_pngSize = 14958;

    extern const char*   clear1_png;
    const int            clear1_pngSize = 17089;

    extern const char*   flower1_png;
    const int            flower1_pngSize = 22287;

    extern const char*   flower2_png;
    const int            flower2_pngSize = 3299;

    extern const char*   flowerG_png;
    const int            flowerG_pngSize = 38432;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 5;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
