// 从flowmap获取流向
float3 flowDir = tex2D(_FlowMap,i.uv) * 2.0 - 1.0;

// 随着时间进行，采样的变形会越来越夸张，因此需要通过frac函数把偏移范围控制在[0,1]之内
float phase = frac(_Time);

// 时间到达最大值之后会跳变至0，为了解决这个问题需要构造两层相差半个周期的采样
float phase0 = frac(_Time * 0.1 * _TimeSpeed);
float phase1 = frac(_Time * 0.1 * _TimeSpeed + 0.5);

//平铺贴图用的uv
float2 tiling_uv = i.uv * _MainTex_ST.xy + _MainTex_ST.zw;

//用波形函数周期化向量场方向，用偏移后的uv对材质进行偏移采样
half3 tex0 = tex2D(_MainTex, tiling_uv - flowDir.xy * phase0);
half3 tex1 = tex2D(_MainTex, tiling_uv - flowDir.xy * phase1);

//构造函数计算随波形函数变化的权值，使得MainTex采样值在接近最大偏移时权值为0，并因此消隐，构造较平滑的循环
float flowLerp = abs((0.5 - phase0)/0.5);
half3 finalColor = lerp(tex0,tex1,flowLerp);

