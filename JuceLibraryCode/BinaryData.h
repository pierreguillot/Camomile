/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   CreditsAU;
    const int            CreditsAUSize = 443;

    extern const char*   CreditsVST;
    const int            CreditsVSTSize = 501;

    extern const char*   clear1_png;
    const int            clear1_pngSize = 5839;

    extern const char*   clear2_png;
    const int            clear2_pngSize = 11853;

    extern const char*   copy1_png;
    const int            copy1_pngSize = 5601;

    extern const char*   copy2_png;
    const int            copy2_pngSize = 13753;

    extern const char*   flower_center_png;
    const int            flower_center_pngSize = 3299;

    extern const char*   flower_petals_png;
    const int            flower_petals_pngSize = 22287;

    extern const char*   option_png;
    const int            option_pngSize = 29484;

    extern const char*   DejaVuSansMono_ttf;
    const int            DejaVuSansMono_ttfSize = 340712;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 10;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
