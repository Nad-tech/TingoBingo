#version 330

// Vertex attributes supplied by raylib.
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Standard raylib transformation matrices.
uniform mat4 mvp;
uniform mat4 matModel;

// Data passed to the fragment shader.
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 fragNormal;

void main()
{
    // Transform the vertex into world space.
    vec4 worldPosition = matModel * vec4(vertexPosition, 1.0);

    fragPosition = worldPosition.xyz;
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    // Transform the normal correctly for lighting.
    mat3 normalMatrix = transpose(inverse(mat3(matModel)));

    fragNormal = normalize(normalMatrix * vertexNormal);

    // Calculate the final vertex position.
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}