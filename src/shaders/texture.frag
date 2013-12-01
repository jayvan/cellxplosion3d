varying float albedo, specular;
uniform sampler2D texture;
varying vec2 vTexCoord;

void main() {
    vec4 ambientp = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
    vec4 diffusep = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
    vec4 specularp = gl_LightSource[0].specular * gl_FrontMaterial.specular;
    vec4 texturep = texture2D(texture, vTexCoord).rgba;

    gl_FragColor = (ambientp + albedo * diffusep + specular*specularp) * (texturep);
}
