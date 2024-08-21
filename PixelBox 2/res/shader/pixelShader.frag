
uniform sampler2D pixelTexture;

uniform vec2 worldSize;
uniform float zoomLevel;

void main(){
    vec2 uv = gl_TexCoord[0].xy;
    vec2 pixelUV = fract(uv * worldSize);
    vec2 pixelSize = 1.0 / worldSize;

    vec4 color = texture2D(pixelTexture, uv);
    
    // Anti-aliasing
    vec4 sum = vec4(0.0);
    float count = 0;

    //FIXME: using 0.5 works but has some artifacts when zoomed out. 1.0 is better but increases gpu usage. using 1.0 and cap at 5 works good
    int numSamples = min(5, max(1, int(1.0 / zoomLevel)));

    vec2 sampleOffset = pixelSize * 0.5 / (zoomLevel * numSamples);
    for(int x = -numSamples; x <= numSamples; ++x){
        for(int y = -numSamples; y <= numSamples; ++y){
            vec2 offset = vec2(x, y) * sampleOffset;
            float factor = 1.0;//max(0.0, 1.0 - length(offset/w));
            sum += texture2D(pixelTexture, uv + offset) * factor;
            count += factor;
        }
    }
    color = sum / count;
    
    

    gl_FragColor = color;
}