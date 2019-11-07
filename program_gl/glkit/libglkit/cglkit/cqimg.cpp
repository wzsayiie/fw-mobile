#include "cqimg.h"
#include "cqcppbasis.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void initIfNeeded() {
    cq_synchronize({
        static bool ready = false;
        if (ready) {
            return;
        };
        ready = true;
        
        stbi_set_flip_vertically_on_load(true);
    });
}

static cq_tex *move_stbi(int pw, int ph, int comp, stbi_uc *data) {
    cq_tex *tex = nullptr;
    
    if (data != nullptr) {
        if (comp == 3) {
            tex = cq_new_rgb_tex(pw, ph, data);
        } else if (comp == 4) {
            tex = cq_new_tex(pw, ph, data);
        }
    }
    stbi_image_free(data);
    
    return tex;
}

cq_tex *cq_img_from_data(const uint8_t *data, int32_t len) {
    initIfNeeded();
    
    int pw = 0, ph = 0, comp = 0;
    stbi_uc *img = stbi_load_from_memory(data, len, &pw, &ph, &comp, 0);
    
    return move_stbi(pw, ph, comp, img);
}

cq_tex *cq_img_from_file(const char *path) {
    initIfNeeded();
    
    int pw = 0, ph = 0, comp = 0;
    stbi_uc *img = stbi_load(path, &pw, &ph, &comp, 0);

    return move_stbi(pw, ph, comp, img);
}
