struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 worldPos : POSITION0;
};

struct Light
{
    float4 color;
    float3 pos;
    float range;
 
};

cbuffer LightBuf : register(b0)
{
    Light lights[1000];
  
};

cbuffer isLight : register(b1)
{
    int isLight;
    int lightNum;
    int dummy1,  dummy3;
}

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main (PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

    if (isLight == 1)
    {
        //ピクセルの1点に対して。全ての点光源の明るさを計算する
        for (int i = 1; i < lightNum; ++i)
        {
        //各ピクセルから点光源に向かうベクトルを計算
            float3 toLightVec = lights[i].pos - pin.worldPos.xyz;
            float3 V = normalize(toLightVec); //ベクトル正規化
            float3 toLightLen = length(toLightVec); //光源までの距離

        //点光源に向かうベクトルと法線から明るさを計算
            float3 N = normalize(pin.normal);
            float dotNV = saturate(dot(N, V));

        //距離に応じて光の強さを変える
        //距離が近つければ明るく離れていればくらくなるよう計算
            float3 attenuation = saturate(1.0f - toLightLen / lights[i].range);

        //自然な減衰の計算
        //距離に応じて光のあたる面が乗算で増えていく
            attenuation = pow(attenuation, 2.0f);

        //複数の点光源の光を合算していく
            color.rgb += lights[i].color.rgb * dotNV * attenuation;
	    
        }
    }
    else
    {
        if (lightNum != 0)
	    {
		     //各ピクセルから点光源に向かうベクトルを計算
            float3 toLightVec = lights[0].pos - pin.worldPos.xyz;
            float3 V = normalize(toLightVec); //ベクトル正規化
            float3 toLightLen = length(toLightVec); //光源までの距離

        //点光源に向かうベクトルと法線から明るさを計算
            float3 N = normalize(pin.normal);
            float dotNV = saturate(dot(N, V));

        //距離に応じて光の強さを変える
        //距離が近つければ明るく離れていればくらくなるよう計算
            float3 attenuation = saturate(1.0f - toLightLen / lights[0].range);

        //自然な減衰の計算
        //距離に応じて光のあたる面が乗算で増えていく
            attenuation = pow(attenuation, 2.0f);

        //複数の点光源の光を合算していく
            color.rgb += lights[0].color.rgb * dotNV * attenuation;
        }
    }
    
	
    return color;
}