float cosTheta = dot(lightDir, N);  

// Fresnel Schlick
vec3 F0 = vec3(0.04);
F0      = mix(F0, surfaceColor.rgb, metalness);

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

