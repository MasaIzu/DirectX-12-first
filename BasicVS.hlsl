cbuffer ConstBufferDataMaterialPos : register(b0)
{
	float4 move; // ˆÚ“®
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}