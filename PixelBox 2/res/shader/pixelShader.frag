
uniform sampler2D pixelTexture;

uniform vec2 worldSize;
uniform float zoomLevel;

void main(){
    vec2 uv = gl_TexCoord[0].xy;
    vec2 pixelUV = fract(uv * worldSize);

    vec4 color = texture2D(pixelTexture, uv);
    // color = vec4(pixelUV, 0.0, 1.0);
    

    gl_FragColor = color;
}