--------------------------------------------------------------------
-- This file was automatically generated by ProjectGenerator
-- which is tooling part the build system designed for GUCEF
--     (Galaxy Unlimited Framework)
-- For the latest info, see http://www.VanvelzenSoftware.com/
--
-- The contents of this file are placed in the public domain. Feel
-- free to make use of it in any way you like.
--------------------------------------------------------------------
--

-- Configuration for module: freetype


project( "freetype" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C" )



configuration( {} )
kind( "SharedLib" )


configuration( {} )
defines( { "FT2_BUILD_LIBRARY", "FT_CONFIG_OPTION_SYSTEM_ZLIB", "FT_CONFIG_OPTION_USE_ZLIB", "FT_DVEDIT_BUILD_DLL", "FT_DVEDIT_DLL_API" } )
  links( { "z" } )
  
configuration( { LINUX } )
links( { "zlib" } )
  links( { "zlib" } )
  
configuration( { WIN32 } )
links( { "zlib" } )
  links( { "zlib" } )
  
configuration( { WIN64 } )
links( { "zlib" } )
  links( { "zlib" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/ft2build.h",
  "include/freetype/freetype.h",
  "include/freetype/ftbbox.h",
  "include/freetype/ftbdf.h",
  "include/freetype/ftbitmap.h",
  "include/freetype/ftcache.h",
  "include/freetype/ftchapters.h",
  "include/freetype/ftcid.h",
  "include/freetype/fterrdef.h",
  "include/freetype/fterrors.h",
  "include/freetype/ftgasp.h",
  "include/freetype/ftglyph.h",
  "include/freetype/ftgxval.h",
  "include/freetype/ftgzip.h",
  "include/freetype/ftimage.h",
  "include/freetype/ftincrem.h",
  "include/freetype/ftlcdfil.h",
  "include/freetype/ftlist.h",
  "include/freetype/ftlzw.h",
  "include/freetype/ftmm.h",
  "include/freetype/ftmodapi.h",
  "include/freetype/ftmoderr.h",
  "include/freetype/ftotval.h",
  "include/freetype/ftoutln.h",
  "include/freetype/ftpfr.h",
  "include/freetype/ftrender.h",
  "include/freetype/ftsizes.h",
  "include/freetype/ftsnames.h",
  "include/freetype/ftstroke.h",
  "include/freetype/ftsynth.h",
  "include/freetype/ftsystem.h",
  "include/freetype/fttrigon.h",
  "include/freetype/fttypes.h",
  "include/freetype/ftwinfnt.h",
  "include/freetype/ftxf86.h",
  "include/freetype/t1tables.h",
  "include/freetype/ttnameid.h",
  "include/freetype/tttables.h",
  "include/freetype/tttags.h",
  "include/freetype/ttunpat.h",
  "include/freetype/config/ftconfig.h",
  "include/freetype/config/ftheader.h",
  "include/freetype/config/ftmodule.h",
  "include/freetype/config/ftoption.h",
  "include/freetype/config/ftstdlib.h",
  "include/freetype/internal/autohint.h",
  "include/freetype/internal/ftcalc.h",
  "include/freetype/internal/ftdebug.h",
  "include/freetype/internal/ftdriver.h",
  "include/freetype/internal/ftgloadr.h",
  "include/freetype/internal/ftmemory.h",
  "include/freetype/internal/ftobjs.h",
  "include/freetype/internal/ftrfork.h",
  "include/freetype/internal/ftserv.h",
  "include/freetype/internal/ftstream.h",
  "include/freetype/internal/fttrace.h",
  "include/freetype/internal/ftvalid.h",
  "include/freetype/internal/internal.h",
  "include/freetype/internal/pcftypes.h",
  "include/freetype/internal/psaux.h",
  "include/freetype/internal/pshints.h",
  "include/freetype/internal/sfnt.h",
  "include/freetype/internal/t1types.h",
  "include/freetype/internal/tttypes.h",
  "include/freetype/internal/services/svbdf.h",
  "include/freetype/internal/services/svcid.h",
  "include/freetype/internal/services/svgldict.h",
  "include/freetype/internal/services/svgxval.h",
  "include/freetype/internal/services/svkern.h",
  "include/freetype/internal/services/svmm.h",
  "include/freetype/internal/services/svotval.h",
  "include/freetype/internal/services/svpfr.h",
  "include/freetype/internal/services/svpostnm.h",
  "include/freetype/internal/services/svpscmap.h",
  "include/freetype/internal/services/svpsinfo.h",
  "include/freetype/internal/services/svsfnt.h",
  "include/freetype/internal/services/svttcmap.h",
  "include/freetype/internal/services/svtteng.h",
  "include/freetype/internal/services/svttglyf.h",
  "include/freetype/internal/services/svwinfnt.h",
  "include/freetype/internal/services/svxf86nm.h",
  "src/winfonts/fnterrs.h",
  "src/winfonts/winfnt.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/autofit/autofit.c",
  "src/base/ftbase.c",
  "src/base/ftsystem.c",
  "src/base/ftglyph.c",
  "src/base/ftbitmap.c",
  "src/base/ftinit.c",
  "src/bdf/bdf.c",
  "src/cache/ftcache.c",
  "src/cff/cff.c",
  "src/cid/cidriver.c",
  "src/cid/cidobjs.c",
  "src/cid/cidgload.c",
  "src/cid/cidload.c",
  "src/cid/cidparse.c",
  "src/gxvalid/gxvalid.c",
  "src/gzip/ftgzip.c",
  "src/lzw/ftlzw.c",
  "src/otvalid/otvalid.c",
  "src/pcf/pcf.c",
  "src/pfr/pfr.c",
  "src/psaux/psaux.c",
  "src/pshinter/pshinter.c",
  "src/psnames/psnames.c",
  "src/raster/raster.c",
  "src/sfnt/sfnt.c",
  "src/smooth/ftsmooth.c",
  "src/smooth/ftgrays.c",
  "src/truetype/truetype.c",
  "src/type1/type1.c",
  "src/type42/type42.c",
  "src/winfonts/winfnt.c"
 } )



configuration( { "ANDROID" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "GLX" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "GTK" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "IPHONEOS" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "LINUX" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "OSX" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "SDL" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "SYMBIAN" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "UNIX" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "WIN32" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/autofit/autofit.c",
      "src/base/ftbase.c",
      "src/base/ftsystem.c",
      "src/base/ftglyph.c",
      "src/base/ftbitmap.c",
      "src/base/ftinit.c",
      "src/bdf/bdf.c",
      "src/cache/ftcache.c",
      "src/cff/cff.c",
      "src/cid/cidriver.c",
      "src/cid/cidobjs.c",
      "src/cid/cidgload.c",
      "src/cid/cidload.c",
      "src/cid/cidparse.c",
      "src/gxvalid/gxvalid.c",
      "src/gzip/ftgzip.c",
      "src/lzw/ftlzw.c",
      "src/otvalid/otvalid.c",
      "src/pcf/pcf.c",
      "src/pfr/pfr.c",
      "src/psaux/psaux.c",
      "src/pshinter/pshinter.c",
      "src/psnames/psnames.c",
      "src/raster/raster.c",
      "src/sfnt/sfnt.c",
      "src/smooth/ftsmooth.c",
      "src/smooth/ftgrays.c",
      "src/truetype/truetype.c",
      "src/type1/type1.c",
      "src/type42/type42.c"
    } )


configuration( {} )
includedirs( { "include", "include/freetype", "include/freetype/config", "include/freetype/internal", "include/freetype/internal/services", "src/winfonts" } )

configuration( { "LINUX" } )
includedirs( { "../zlib" } )

configuration( { "WIN32" } )
includedirs( { "../zlib" } )

configuration( { "WIN64" } )
includedirs( { "../zlib" } )
