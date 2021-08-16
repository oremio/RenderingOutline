RayTracing(original_point, ray_direction, objects, depth)
{
    if(depth > maxDepth)
        return color(0,0,0);
    if(IsHitObject(original_point, ray_direction, objects))
    {
        hitPoint = GetHitPoint();
        normal = GetNormal();

        reflectionDirection = reflect(ray_direction, normal);
        refractionDirection = refract(ray_direction, normal);

        local_color = BlinnPhongShader(original_point, normal, light_position);

        return local_color 
            + k1 * RayTracing(hitPoint, reflectionDirection, objects, depth + 1)
            + k2 * RayTracing(hitPoint, refractionDirection, objects, depth + 1);
    }
    else
        return background_color;
}
