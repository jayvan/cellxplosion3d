uniform sampler2D texture;
varying vec2 vTexCoord;

void main() {
    vec4 texturep = texture2D(texture, vTexCoord).rgba;
    gl_FragColor = texturep;
}

