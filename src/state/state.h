#ifndef GSTATE_H
#define GSTATE_H

#define GRAPHICS_API_OPENGL_43

#include <raylib.h>
#include <rcamera.h> // raylib camera

#include "../light.h"
#include "../player.h"
#include "../psystem.h"
#include "../terrain.h"
#include "../enemy.h"
#include "../item.h"
#include "../gui.h"
#include "../shader_util.h"
#include "../npc.h"
#include "../config.h"
#include "../fog.h"

// Enable: "Noclip", "Dev menu", "Render debug info"
#define DEV_MODE 1


#define DEFAULT_RES_X 1500  // If resolution is not found from config file
#define DEFAULT_RES_Y 800   // use default resolution.
#define DEFAULT_SSAO_KERNEL_SAMPLES 32

#define RESOLUTION_X 1500
#define RESOLUTION_Y 800

#define MAX_RENDERDIST 8000.0
#define MIN_RENDERDIST 2200.0

#define TARGET_FPS 500
#define CAMERA_SENSETIVITY 0.00125
#define MAX_VOLUME_DIST 720 // How far away can player hear sounds.?

#define GRAVITY_CONST 500
#define FONT_SPACING 1.0

#define FOG_MIN 1.0
#define FOG_MAX 10.0

// Index for 'textures'.
#define NONE_TEXID -1 // TODO: remove this <-
#define GRID4x4_TEXID 0
#define GRID6x6_TEXID 1
#define GRID9x9_TEXID 2
#define GUN_0_TEXID 3
#define ENEMY_LVL0_TEXID 4
#define PLAYER_ARMS_TEXID 5
#define CRITICALHIT_TEXID 6
#define TREEBARK_TEXID 7
#define LEAF_TEXID 8
#define ROCK_TEXID 9
#define TERRAIN_TEXID 10
#define GRASS_TEXID 11
#define APPLE_INV_TEXID 12
#define APPLE_TEXID 13
#define METALPIECE_INV_TEXID 14
#define METALPIECE_TEXID 15
#define PLAYER_SKIN_TEXID 16
#define PLAYER_HANDS_TEXID 17
#define METAL2_TEXID 18
#define ENEMY_LVL1_TEXID 19
#define MUSHROOM_HAT_TEXID 20
#define MUSHROOM_BODY_TEXID 21
#define TERRAIN_MUSHROOM_TEXID 22
#define HAZYBIOME_GROUND_TEXID 23
#define EVILBIOME_GROUND_TEXID 24
#define MAX_TEXTURES 25
// ...


// Index for 'sounds'
#define PLAYER_GUN_SOUND 0
#define ENEMY_HIT_SOUND_0 1
#define ENEMY_HIT_SOUND_1 2
#define ENEMY_HIT_SOUND_2 3
#define ENEMY_GUN_SOUND 4
#define PRJ_ENVHIT_SOUND 5
#define PLAYER_HIT_SOUND 6
#define ENEMY_EXPLOSION_SOUND 7
#define POWERUP_SOUND 8
#define CLOUDBURST_SOUND 9
#define MAX_SOUNDS 10
//...


// Index for 'shaders'   | TODO: Delete unused shaders.
#define DEFAULT_SHADER 0
#define POSTPROCESS_SHADER 1
#define BLOOM_TRESHOLD_SHADER 2
#define PRJ_ENVHIT_PSYS_SHADER 3
#define BASIC_WEAPON_PSYS_SHADER 4
#define FOLIAGE_SHADER 5
#define FOG_PARTICLE_SHADER 6
#define WATER_SHADER 7
#define GUNFX_SHADER 8
#define ENEMY_GUNFX_SHADER 9
#define EXPLOSION_PSYS_SHADER 10
#define PLAYER_HIT_SHADER 11
#define GBUFFER_SHADER 12
#define GBUFFER_INSTANCE_SHADER 13
#define GBUFFER_FOLIAGE_WIND_SHADER 14
#define SSAO_SHADER 15
#define BLOOM_BLUR_SHADER 16
#define SSAO_BLUR_SHADER 17
#define SKY_SHADER 18
#define CLOUD_PARTICLE_SHADER 19
#define FOLIAGE_WIND_SHADER 20
#define MAX_SHADERS 22
// ...
 

// Global particle systems:
#define PLAYER_WEAPON_PSYS 0
#define ENEMY_WEAPON_PSYS 1
#define PROJECTILE_ENVHIT_PSYS 2
#define ENEMY_HIT_PSYS 3
#define FOG_EFFECT_PSYS 4
#define PLAYER_HIT_PSYS 5
#define EXPLOSION_PSYS 6
#define WATER_SPLASH_PSYS 7
#define ENEMY_GUNFX_PSYS 8
#define CLOUD_PSYS 9
#define PRJ_TRAIL_PSYS 10
#define MAX_PSYSTEMS 11
// ...


// Normal lights:
#define SUN_NLIGHT 0
#define PLAYER_GUN_NLIGHT 1
// ...

// How many lights can decay at once?
#define LIGHT_UB_STRUCT_SIZE (4*4 + 4*4 + 4*4 + 4*4)
#define FOG_UB_STRUCT_SIZE (4*4 + 4*4 + 4*4)


// Uniform buffer objects.
#define FOG_UBO 0
#define LIGHTS_UBO 1     // "Normal" lights
#define PRJLIGHTS_UBO 2  // Projectile lights.
#define MAX_UBOS 3


#define ENEMY_LVL0_WEAPON 0
#define ENEMY_LVL1_WEAPON 1
#define MAX_ENEMY_WEAPONS 2


#define MAX_ALL_ENEMIES 64 // Total max enemies.
#define MAX_ENEMY_MODELS 2

#define NUM_BLOOM_DOWNSAMPLES 2


//#define MAX_RENDER_CRITHITS 8

// Static lights in lights ubo
#define SUN_LIGHT_ID 0
#define PLAYER_GUN_LIGHT_ID 1
#define MAX_STATIC_LIGHTS 2

// Dynamic lights in lights ubo
#define EXPLOSION_LIGHTS_ID 3
#define MAX_EXPLOSION_LIGHTS (MAX_NORMAL_LIGHTS - MAX_STATIC_LIGHTS)


// IMPORTANT NOTE: This must be same as in 'res/shaders/ssao.fs'
#define MAX_SSAO_KERNEL_SIZE 128

#define MAX_SHADOW_LEVELS 3



// Critical hit marker.
struct crithit_marker_t {
    Vector3 position;
    float   lifetime; // Scale smaller overtime.
    int     visible;
    float   dst; // Distance to player. Used for sorting to fix alpha blending.
};


struct gbuffer_t {
    unsigned int normal_tex;
    unsigned int position_tex;
    unsigned int difspec_tex; // (Currently not used.)
    unsigned int depth_tex;

    unsigned int framebuffer;
    unsigned int depthbuffer;

    int res_x;
    int res_y;
};

// Sets the fog density automatically to 'render_dist'
// 'density' variable in fog_t struct will be ignored.
#define FOG_MODE_RENDERDIST 0

// Density can be controlled arbitrarily. range: 0 - 10.0
#define FOG_MODE_CUSTOM 1   // TODO



struct weather_t {
    Color   sun_color;
    Vector3 wind_dir;
    float   wind_strength;
    // ...
};


struct gamepad_t {
    int id;
    Vector2 Lstick;
    Vector2 Rstick;
    Vector2 Rstick_delta;
    float sensetivity;
};



// Game state "gst".
struct state_t {
    float time;
    float dt; // Previous frame time.
    struct player_t player;
    Font font;
    platform_file_t cfgfile;
    struct config_t cfg;
    struct gamepad_t gamepad;

    unsigned int ubo[MAX_UBOS];
    size_t num_prj_lights;

    struct fog_t      fog;
    struct weather_t  weather;

    Shader               shaders[MAX_SHADERS];
    struct shaderutil_t  shader_u[MAX_SHADERS]; // Store uniform locations for shaders.

    Texture       textures[MAX_TEXTURES];
    unsigned int  num_textures;

    // Light can be added to this array to be decayed/dimmed over time before disabling them completely.
    struct light_t decay_lights[MAX_DECAY_LIGHTS];
    size_t next_explosion_light_index;

    struct psystem_t psystems[MAX_PSYSTEMS];
    struct terrain_t terrain;

    struct npc_t npc;

    //struct spawn_system_t spawnsys;
    struct ent_spawnsys_t enemy_spawn_systems[MAX_ENEMY_TYPES];
    Model  enemy_models[MAX_ENEMY_MODELS];
    struct enemy_t enemies[MAX_ALL_ENEMIES];
    size_t num_enemies;
    size_t num_enemies_rendered;

    struct weapon_t enemy_weapons[MAX_ENEMY_WEAPONS];
    size_t num_enemy_weapons;


    struct item_t items[MAX_ALL_ITEMS];
    Model         item_models[MAX_ITEM_MODELS];
    size_t        num_items;

    float         natural_item_spawn_timers[MAX_ITEM_TYPES];

    int rseed; // Seed for randomgen functions.
    int debug;

    float render_dist; // Render distance.

    /*
    struct crithit_marker_t crithit_markers[MAX_RENDER_CRITHITS];
    size_t num_crithit_markers;
    float  crithit_marker_maxlifetime;
    */

    int xp_update_done;
    int xp_update_target;
    int xp_update_add;
    float xp_update_timer;
    float xp_value_f;

    int    has_audio;
    Sound  sounds[MAX_SOUNDS];

    // Resolutions
    int res_x;
    int res_y;
    int ssao_res_x;
    int ssao_res_y;
    int shadow_res_x;
    int shadow_res_y;

    Vector2 screen_size;

    struct gbuffer_t gbuffer;  
    struct gbuffer_t shadow_gbuffers[MAX_SHADOW_LEVELS];

    Camera  shadow_cams[MAX_SHADOW_LEVELS];
    float   shadow_cam_height;
    float   shadow_bias;
 

    // Everything is rendered to this texture
    // and then post processed.
    RenderTexture2D env_render_target;
    RenderTexture2D env_render_downsample;
    
    // Bloom treshold is written here.
    // when post processing. bloom is aplied and mixed into 'env_render_target' texture
    RenderTexture2D bloomtresh_target;
        
    int       ssao_enabled;
    Texture   ssao_noise_tex;
    Vector3*  ssao_kernel;
    
    Matrix cam_view_matrix; // TODO: Move these
    Matrix cam_proj_matrix; //

    RenderTexture2D ssao_target;
    RenderTexture2D ssao_final;

    Color render_bg_color; // TODO: Remove this
    int running;
    int menu_open;
    int devmenu_open;
    
    float menu_slider_render_dist_v;
    Model skybox;

    RenderTexture2D bloom_downsamples[NUM_BLOOM_DOWNSAMPLES];

    // This is for gui component.
    Texture  colorpick_tex;
    Image    colorpick_img;

    // Used for when player changes biome.
    float biome_change;
    struct biome_t* old_biome;
    struct biome_t* new_biome;
};


void state_create_ubo(struct state_t* gst, int ubo_index, int binding_point, size_t size);
void state_update_shader_uniforms(struct state_t* gst);
void state_update_frame(struct state_t* gst);
void state_update_shadow_cams(struct state_t* gst);
void state_update_shadow_map_uniforms(struct state_t* gst, int shader_index);

void create_explosion(struct state_t* gst, Vector3 position, float damage, float radius);
void set_render_dist(struct state_t* gst, float new_dist);

// 'shader_index' can be set to negative value so its not used.
void resample_texture(struct state_t* gst,
        RenderTexture2D to, RenderTexture2D from,
        int src_width, int src_height,
        int dst_width, int dst_height, int shader_index);
// Misc.
//void state_add_crithit_marker(struct state_t* gst, Vector3 position);



#endif
