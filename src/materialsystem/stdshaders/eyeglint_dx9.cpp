//===== Copyright � 1996-2007, Valve Corporation, All rights reserved. ======//
//
// Run procedural glint generation inner loop in pixel shader
//
// $Header: $
// $NoKeywords: $
//===========================================================================//

#include "basevsshader.h"
#include "shaderlib/cshader.h"

#include "sdk_eyeglint_vs20.inc"
#include "sdk_eyeglint_ps20.inc"
#include "sdk_eyeglint_ps20b.inc"

DEFINE_FALLBACK_SHADER( sdk_eyeglint, sdk_eyeglint_dx9 )
BEGIN_VS_SHADER( sdk_eyeglint_dx9, "Help for EyeGlint" )

BEGIN_SHADER_PARAMS
END_SHADER_PARAMS

SHADER_INIT
{
}

SHADER_FALLBACK
{
	if ( g_pHardwareConfig->GetDXSupportLevel() < 90 )
	{
		return "Wireframe";
	}
	return 0;
}

SHADER_DRAW
{
	SHADOW_STATE
	{
		pShaderShadow->EnableDepthWrites( false );

		pShaderShadow->EnableBlending( true );
		pShaderShadow->BlendFunc( SHADER_BLEND_ONE, SHADER_BLEND_ONE );		// Additive blending

		int pTexCoords[3] = { 2, 2, 3 };
		pShaderShadow->VertexShaderVertexFormat( VERTEX_POSITION, 3, pTexCoords, 0 );

		pShaderShadow->EnableCulling( false );

		pShaderShadow->EnableSRGBWrite( true );

		DECLARE_STATIC_VERTEX_SHADER( sdk_eyeglint_vs20 );
		SET_STATIC_VERTEX_SHADER( sdk_eyeglint_vs20 );

		SET_STATIC_PS2X_PIXEL_SHADER_NO_COMBOS( sdk_eyeglint );
	}

	DYNAMIC_STATE
	{
		DECLARE_DYNAMIC_VERTEX_SHADER( sdk_eyeglint_vs20 );
		SET_DYNAMIC_VERTEX_SHADER( sdk_eyeglint_vs20 );

		SET_DYNAMIC_PS2X_PIXEL_SHADER_NO_COMBOS( sdk_eyeglint );
	}
	Draw();
}
END_SHADER
