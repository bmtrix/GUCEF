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

-- Configuration for module: RocketCore


project( "RocketCore" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )

configuration( {} )
links( { "freetype" } )
links( { "freetype" } )


configuration( {} )
defines( { "RocketCore_EXPORTS" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "Clock.h",
  "ContextInstancerDefault.h",
  "DebugFont.h",
  "DecoratorNone.h",
  "DecoratorNoneInstancer.h",
  "DecoratorTiled.h",
  "DecoratorTiledBox.h",
  "DecoratorTiledBoxInstancer.h",
  "DecoratorTiledHorizontal.h",
  "DecoratorTiledHorizontalInstancer.h",
  "DecoratorTiledImage.h",
  "DecoratorTiledImageInstancer.h",
  "DecoratorTiledInstancer.h",
  "DecoratorTiledVertical.h",
  "DecoratorTiledVerticalInstancer.h",
  "DocumentHeader.h",
  "ElementBackground.h",
  "ElementBorder.h",
  "ElementDecoration.h",
  "ElementDefinition.h",
  "ElementHandle.h",
  "ElementImage.h",
  "ElementStyle.h",
  "ElementTextDefault.h",
  "EventDispatcher.h",
  "EventInstancerDefault.h",
  "EventIterators.h",
  "FileInterfaceDefault.h",
  "FontEffectNone.h",
  "FontEffectNoneInstancer.h",
  "FontEffectOutline.h",
  "FontEffectOutlineInstancer.h",
  "FontEffectShadow.h",
  "FontEffectShadowInstancer.h",
  "FontFace.h",
  "FontFaceHandle.h",
  "FontFaceLayer.h",
  "FontFamily.h",
  "GeometryDatabase.h",
  "LayoutBlockBox.h",
  "LayoutBlockBoxSpace.h",
  "LayoutEngine.h",
  "LayoutInlineBox.h",
  "LayoutInlineBoxText.h",
  "LayoutLineBox.h",
  "PluginRegistry.h",
  "Pool.h",
  "precompiled.h",
  "PropertyParserColour.h",
  "PropertyParserKeyword.h",
  "PropertyParserNumber.h",
  "PropertyParserString.h",
  "PropertyShorthandDefinition.h",
  "StreamFile.h",
  "StringCache.h",
  "StyleSheetFactory.h",
  "StyleSheetNode.h",
  "StyleSheetNodeSelector.h",
  "StyleSheetNodeSelectorEmpty.h",
  "StyleSheetNodeSelectorFirstChild.h",
  "StyleSheetNodeSelectorFirstOfType.h",
  "StyleSheetNodeSelectorLastChild.h",
  "StyleSheetNodeSelectorLastOfType.h",
  "StyleSheetNodeSelectorNthChild.h",
  "StyleSheetNodeSelectorNthLastChild.h",
  "StyleSheetNodeSelectorNthLastOfType.h",
  "StyleSheetNodeSelectorNthOfType.h",
  "StyleSheetNodeSelectorOnlyChild.h",
  "StyleSheetNodeSelectorOnlyOfType.h",
  "StyleSheetParser.h",
  "Template.h",
  "TemplateCache.h",
  "TextureDatabase.h",
  "TextureLayout.h",
  "TextureLayoutRectangle.h",
  "TextureLayoutRow.h",
  "TextureLayoutTexture.h",
  "TextureResource.h",
  "UnicodeRange.h",
  "WidgetSlider.h",
  "WidgetSliderScroll.h",
  "XMLNodeHandlerBody.h",
  "XMLNodeHandlerDefault.h",
  "XMLNodeHandlerHead.h",
  "XMLNodeHandlerTemplate.h",
  "XMLParseTools.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "BaseXMLParser.cpp",
  "Box.cpp",
  "Clock.cpp",
  "Context.cpp",
  "ContextInstancer.cpp",
  "ContextInstancerDefault.cpp",
  "ConvolutionFilter.cpp",
  "Core.cpp",
  "Decorator.cpp",
  "DecoratorInstancer.cpp",
  "DecoratorNone.cpp",
  "DecoratorNoneInstancer.cpp",
  "DecoratorTiled.cpp",
  "DecoratorTiledBox.cpp",
  "DecoratorTiledBoxInstancer.cpp",
  "DecoratorTiledHorizontal.cpp",
  "DecoratorTiledHorizontalInstancer.cpp",
  "DecoratorTiledImage.cpp",
  "DecoratorTiledImageInstancer.cpp",
  "DecoratorTiledInstancer.cpp",
  "DecoratorTiledVertical.cpp",
  "DecoratorTiledVerticalInstancer.cpp",
  "Dictionary.cpp",
  "DocumentHeader.cpp",
  "Element.cpp",
  "ElementBackground.cpp",
  "ElementBorder.cpp",
  "ElementDecoration.cpp",
  "ElementDefinition.cpp",
  "ElementDocument.cpp",
  "ElementHandle.cpp",
  "ElementImage.cpp",
  "ElementInstancer.cpp",
  "ElementReference.cpp",
  "ElementScroll.cpp",
  "ElementStyle.cpp",
  "ElementText.cpp",
  "ElementTextDefault.cpp",
  "ElementUtilities.cpp",
  "Event.cpp",
  "EventDispatcher.cpp",
  "EventInstancer.cpp",
  "EventInstancerDefault.cpp",
  "EventListenerInstancer.cpp",
  "Factory.cpp",
  "FileInterface.cpp",
  "FileInterfaceDefault.cpp",
  "FontDatabase.cpp",
  "FontEffect.cpp",
  "FontEffectInstancer.cpp",
  "FontEffectNone.cpp",
  "FontEffectNoneInstancer.cpp",
  "FontEffectOutline.cpp",
  "FontEffectOutlineInstancer.cpp",
  "FontEffectShadow.cpp",
  "FontEffectShadowInstancer.cpp",
  "FontFace.cpp",
  "FontFaceHandle.cpp",
  "FontFaceLayer.cpp",
  "FontFamily.cpp",
  "Geometry.cpp",
  "GeometryDatabase.cpp",
  "GeometryUtilities.cpp",
  "LayoutBlockBox.cpp",
  "LayoutBlockBoxSpace.cpp",
  "LayoutEngine.cpp",
  "LayoutInlineBox.cpp",
  "LayoutInlineBoxText.cpp",
  "LayoutLineBox.cpp",
  "Log.cpp",
  "Plugin.cpp",
  "PluginRegistry.cpp",
  "precompiled.cpp",
  "Property.cpp",
  "PropertyDefinition.cpp",
  "PropertyDictionary.cpp",
  "PropertyParserColour.cpp",
  "PropertyParserKeyword.cpp",
  "PropertyParserNumber.cpp",
  "PropertyParserString.cpp",
  "PropertySpecification.cpp",
  "ReferenceCountable.cpp",
  "RenderInterface.cpp",
  "RocketMath.cpp",
  "RocketString.cpp",
  "Stream.cpp",
  "StreamFile.cpp",
  "StreamMemory.cpp",
  "StringCache.cpp",
  "StringStorage.cpp",
  "StringUtilities.cpp",
  "StyleSheet.cpp",
  "StyleSheetFactory.cpp",
  "StyleSheetNode.cpp",
  "StyleSheetNodeSelector.cpp",
  "StyleSheetNodeSelectorEmpty.cpp",
  "StyleSheetNodeSelectorFirstChild.cpp",
  "StyleSheetNodeSelectorFirstOfType.cpp",
  "StyleSheetNodeSelectorLastChild.cpp",
  "StyleSheetNodeSelectorLastOfType.cpp",
  "StyleSheetNodeSelectorNthChild.cpp",
  "StyleSheetNodeSelectorNthLastChild.cpp",
  "StyleSheetNodeSelectorNthLastOfType.cpp",
  "StyleSheetNodeSelectorNthOfType.cpp",
  "StyleSheetNodeSelectorOnlyChild.cpp",
  "StyleSheetNodeSelectorOnlyOfType.cpp",
  "StyleSheetParser.cpp",
  "StyleSheetSpecification.cpp",
  "SystemInterface.cpp",
  "Template.cpp",
  "TemplateCache.cpp",
  "Texture.cpp",
  "TextureDatabase.cpp",
  "TextureLayout.cpp",
  "TextureLayoutRectangle.cpp",
  "TextureLayoutRow.cpp",
  "TextureLayoutTexture.cpp",
  "TextureResource.cpp",
  "UnicodeRange.cpp",
  "URL.cpp",
  "Variant.cpp",
  "Vector2.cpp",
  "WidgetSlider.cpp",
  "WidgetSliderScroll.cpp",
  "WString.cpp",
  "XMLNodeHandler.cpp",
  "XMLNodeHandlerBody.cpp",
  "XMLNodeHandlerDefault.cpp",
  "XMLNodeHandlerHead.cpp",
  "XMLNodeHandlerTemplate.cpp",
  "XMLParser.cpp",
  "XMLParseTools.cpp"
 } )


configuration( {} )
includedirs( { "../../../freetype/include", "../../../freetype/include/freetype", "../../../freetype/include/freetype/config", "../../../freetype/include/freetype/internal", "../../../freetype/include/freetype/internal/services", "../../../freetype/src/winfonts", "../../Include", "../../Include/Rocket", "../../Include/Rocket/Controls", "../../Include/Rocket/Core", "../../Include/Rocket/Core/Python", "../../Include/Rocket/Debugger" } )
