# nf_EES_lib1
An EES external library with an object-oriented implementation (mostly)

The initial purpose for this library was to enable access to
the NIST fluid database, REFPROP, from F-Chart's Engineering
Equation Solver (EES), to add a few functions as-needed for solving
some steady-state thermodynamic models of ejector refrigeration.

I've also added a few functions needed for accessing CoolProp
from EES to solve steady-state absorption chiller cycle models.
This allows an implementation of LiBr-water functions not
requiring REFPROP.

Currently, the project uses qmake to build the library file
used by EES. However, this was just for convenience and the project
does not use Qt. However, as far as I know, EES supports only windows,
so you need Windows.h for the data types in the DLL entry point call
signature.

To build:
  1. Download and install a compiler, windows SDK, qmake, and make
  2. qmake -makefile -o Makefile "CONFIG+=test" nf_EES_lib1.pro
  3. make

To install:
Copy the nf_EES_lib1.dll file to somewhere in your EES/Userlib directory.

To use:
Consult the function information for external routines within EES.

Note that if REFPROP is not installed on your system, then the user-
defined EES functions that call REFPROP will simply give an error
message because the library file (refprop.dll) will not be found.
