
uniform sampler2D pixelTexture;

uniform sampler2D pixelColorTexture;
uniform sampler2D pixelDetailTexture;

uniform vec2 worldSize;
uniform float zoomLevel;
uniform bool detailMode;

uniform bool drawGrid;
float gridWidth = 2.0;

uniform vec2 mousePos;
uniform float brushSize;

void main(){

    vec2 uv = gl_TexCoord[0].xy;
    vec2 pixelSize = 1.0 / worldSize;
    vec4 color = vec4(0.0);

    // Anti-aliasing
    vec4 sum = vec4(0.0);
    float totalWeight = 0.0;
    //FIXME: using 0.5 works but has some artifacts when zoomed out. 1.0 is better but increases gpu usage. using 1.0 and cap at 5 works good
    int numSamples = int(min(5.0, max(0.0, floor(1.0 / zoomLevel))));
    vec2 sampleOffset = pixelSize * 0.5 / (zoomLevel * float(numSamples));
    //this fixes aritfacts from sampling neighbor pixels + drawing grid
    if(numSamples == 0){
        sampleOffset = vec2(0.0);
    }
    for(int x = -numSamples; x <= numSamples; ++x){
        for(int y = -numSamples; y <= numSamples; ++y){
            vec2 offset = vec2(x, y) * sampleOffset;
            float weight = 1.0;//max(0.0, 1.0 - length(offset/w));
            vec4 pixelData = texture2D(pixelTexture, uv + offset);

            //TODO: add support for ruleset to determine if row should be switched
            bool switchRow = pixelData.g > 1.0/255.0;
            
            vec2 pixelUV = vec2(pixelData.r * 255.0/256.0, 0.0);
            if(switchRow){
                pixelUV.y = 0.5;
            }
            vec4 pixelColor = texture2D(pixelColorTexture, pixelUV);

            if(detailMode){
                pixelUV = pixelUV + fract(abs((uv + offset) * worldSize)) * vec2(1.0/256.0, 0.5);
                float detailFactor = min(1.0, max(0.0, (zoomLevel - 8.0) / 9.0));

                pixelColor = mix(pixelColor, texture2D(pixelDetailTexture, pixelUV), detailFactor);
            }

            sum += pixelColor * weight;
            totalWeight += weight;
        }
    }
    color = sum / totalWeight;
    
    
    //Grid
    vec2 pixelUV = fract(abs(uv * worldSize));
    if(drawGrid && zoomLevel > 5.0){
        float factor = min(1.0, max(0.0, (zoomLevel - 5.0) / 6.0));
        if(pixelUV.x <= gridWidth / zoomLevel ||
            pixelUV.y <= gridWidth / zoomLevel ){
            color = mix(color, vec4(0.1, 0.1, 0.1, 1.0), factor);
        }
    }

    //Brush
    if(brushSize > 1.0){
        if(length(uv*worldSize - mousePos) <= brushSize){
            color += 0.1;
        }
    }

    gl_FragColor = color;
}