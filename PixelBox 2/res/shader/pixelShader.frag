
uniform sampler2D pixelTexture;

uniform sampler2D pixelColorTexture;
uniform sampler2D pixelDetailTexture;

uniform vec2 worldSize;
uniform float zoomLevel;
uniform bool detailMode;

void main(){
    vec2 uv = gl_TexCoord[0].xy;
    vec2 pixelUV = fract(uv * worldSize);
    vec2 pixelSize = 1.0 / worldSize;
    vec4 color = vec4(0.0);

    

    // Anti-aliasing
    vec4 sum = vec4(0.0);
    float totalWeight = 0;

    //FIXME: using 0.5 works but has some artifacts when zoomed out. 1.0 is better but increases gpu usage. using 1.0 and cap at 5 works good
    int numSamples = min(5, max(1, int(1.0 / zoomLevel)));

    vec2 sampleOffset = pixelSize * 0.5 / (zoomLevel * numSamples);
    for(int x = -numSamples; x <= numSamples; ++x){
        for(int y = -numSamples; y <= numSamples; ++y){
            vec2 offset = vec2(x, y) * sampleOffset;
            float weight = 1.0;//max(0.0, 1.0 - length(offset/w));
            vec4 pixelData = texture2D(pixelTexture, uv + offset);

            //TODO: add support for ruleset to determine if row should be switched
            bool switchRow = false;
            
            vec2 pixelUV = vec2(pixelData.r * 255.0/256.0, 0.0);
            if(switchRow){
                pixelUV.y = 0.5;
            }
            vec4 pixelColor = texture2D(pixelColorTexture, pixelUV);

            if(detailMode){
                pixelUV = pixelUV + fract((uv + offset) * worldSize) * vec2(1.0/256.0, 0.5);
                float detailFactor = min(1.0, max(0.0, (zoomLevel - 8.0) / 9.0));

                pixelColor = mix(pixelColor, texture2D(pixelDetailTexture, pixelUV), detailFactor);
            }

            sum += pixelColor * weight;
            totalWeight += weight;
        }
    }
    color = sum / totalWeight;
    
    

    gl_FragColor = color;
}