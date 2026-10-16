#version 330

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

// Material properties supplied by raylib.
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Our lighting settings.
uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform vec3 ambient;

// Final pixel colour.
out vec4 finalColor;

void main()
{
    // Get the model's existing texture and colour.
    vec4 texelColor = texture(texture0, fragTexCoord);

    vec4 baseColor = texelColor * colDiffuse * fragColor;

    // Surface normal.
    vec3 normal = normalize(fragNormal);

    // Direction from the surface towards the light.
    vec3 lightDir = normalize(-lightDirection);

    // Calculate diffuse lighting.
    float diffuseStrength = max(dot(normal, lightDir), 0.0);

    // Direction from the surface towards the camera.
    vec3 viewDir = normalize(viewPos - fragPosition);

    // Calculate a subtle specular highlight.
    vec3 halfDir = normalize(lightDir + viewDir);

    float specularStrength =
        pow(max(dot(normal, halfDir), 0.0), 32.0);

    // Combine ambient and directional lighting.
    vec3 lighting =
        ambient + vec3(0.85, 0.85, 0.85) * diffuseStrength;

    // Apply the lighting while preserving the material colour.
    vec3 colour = baseColor.rgb * lighting;

    // Add a restrained highlight.
    colour += vec3(0.12) * specularStrength;

    finalColor = vec4(colour, baseColor.a);
}