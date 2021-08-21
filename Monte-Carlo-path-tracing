shade(p, wo)
{
    #contribution from the light source.
    L_dir = 0.0
    Uniformly sample the light at x' (pdf_light = 1 / A) // 采样
    Shoot a ray from p to x'
    If the ray is not blocked in the middle
        L_dir = L_i * f_r * cosθ * cosθ' / |x' - p|^2 / pdf_light
    
    #contribution from other reflectors.
    L_dir = 0.0
    Test Russian Roulette with probability P_RR // 俄罗斯轮盘赌解决递归问题
    Uniformly sample the hemisphere towara wi (pdf_hemi = 1 / 2pi) // 采样
    Trace a ray r(p, wi)
    If ray r hit a non-emitting object at q
        L_indir = shade(q, -wi) * f_r * cosθ / pdf_hemi / P_RR

    Return L_Dir + L_indir
}