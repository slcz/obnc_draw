#include ".obnc/Draw.h"

#include <obnc/OBNC.h>
#include <simple2d.h>

#define OBERON_SOURCE_FILENAME "Draw.obn"

const int Draw__Pair_id;
const int *const Draw__Pair_ids[1] = {&Draw__Pair_id};
const OBNC_Td Draw__Pair_td = {Draw__Pair_ids, 1};

const int Draw__Color_id;
const int *const Draw__Color_ids[1] = {&Draw__Color_id};
const OBNC_Td Draw__Color_td = {Draw__Color_ids, 1};

const int Draw__Point_id;
const int *const Draw__Point_ids[1] = {&Draw__Point_id};
const OBNC_Td Draw__Point_td = {Draw__Point_ids, 1};

static S2D_Window * window;
static int fg_r, fg_g, fg_b, fg_a;
void (*keydown_fn)(long int);
void (*keyup_fn)(long int);
void (*keyheld_fn)(long int);
void (*mousedown_fn)(const struct Draw__Pair_ *, OBNC_INTEGER, int);
void (*mouseup_fn)(const struct Draw__Pair_ *, OBNC_INTEGER, int);
void (*mousescroll_fn)(
    const struct Draw__Pair_ *,
    OBNC_INTEGER,
    const struct Draw__Pair_ *
);
void (*mousemove_fn)(
    const struct Draw__Pair_ *,
    const struct Draw__Pair_ *
);

static void on_mouse(S2D_Event e)
{
    struct Draw__Pair_ pos, delta;
    int button = 0;
    pos.x_ = e.x; pos.y_ = e.y;
    switch (e.button) {
    case S2D_MOUSE_LEFT:
        button = Draw__MOUSE_LEFT_; break;
    case S2D_MOUSE_MIDDLE:
        button = Draw__MOUSE_MIDDLE_; break;
    case S2D_MOUSE_RIGHT:
        button = Draw__MOUSE_RIGHT_; break;
    case S2D_MOUSE_X1:
        button = Draw__MOUSE_X1_; break;
    case S2D_MOUSE_X2:
        button = Draw__MOUSE_X2_; break;
    }
    delta.x_ = e.delta_x;
    delta.y_ = e.delta_y;
    switch (e.type) {
    case S2D_MOUSE_DOWN:
        if (mousedown_fn)
            mousedown_fn(&pos, button, e.dblclick);
        break;
    case S2D_MOUSE_UP:
        if (mouseup_fn)
            mouseup_fn(&pos, button, e.dblclick);
        break;
    case S2D_MOUSE_SCROLL:
        if (mousescroll_fn)
            mousescroll_fn(&pos, button, &delta);
        break;
    case S2D_MOUSE_MOVE:
        if (mousemove_fn)
            mousemove_fn(&pos, &delta);
        break;
    }
}

static void on_key(S2D_Event e)
{
    switch (e.type) {
        case S2D_KEY_DOWN:
            if (keydown_fn)
                keydown_fn((long)*(e.key));
            break;
        case S2D_KEY_UP:
            if (keyup_fn)
                keyup_fn((long)*(e.key));
            break;
        case S2D_KEY_HELD:
            if (keyheld_fn)
                keyheld_fn((long)*(e.key));
            break;
    }
}

void Draw__create_(const char title_[], OBNC_INTEGER title_len, const struct Draw__Pair_ *size_, Draw__Update_ update_, Draw__Render_ render_, unsigned OBNC_INTEGER flag_)
{
    int flag = 0;
    if ((flag_ & (1 << Draw__CANVAS_RESIZABLE_)) != 0)
        flag |= S2D_RESIZABLE;
    if ((flag_ & (1 << Draw__CANVAS_BORDERLESS_)) != 0)
        flag |= S2D_BORDERLESS;
    if ((flag_ & (1 << Draw__CANVAS_FULLSCREEN_)) != 0)
        flag |= S2D_FULLSCREEN;
    if ((flag_ & (1 << Draw__CANVAS_HIGHDPI_)) != 0)
        flag |= S2D_HIGHDPI;
    window = S2D_CreateWindow(
        title_, size_->x_, size_->y_, update_, render_, flag);
    window->on_key = on_key;
    window->on_mouse = on_mouse;
}


void Draw__show_(void)
{
    S2D_Show((S2D_Window*)window);
}

void Draw__foreground_(const struct Draw__Color_ *color_)
{
    fg_r = color_->r_;
    fg_g = color_->g_;
    fg_b = color_->b_;
    fg_a = color_->a_;
}

void Draw__background_(const struct Draw__Color_ *color_)
{
    window->background.r = color_->r_;
    window->background.g = color_->g_;
    window->background.b = color_->b_;
    window->background.a = color_->a_;
}

void Draw__monotriangle_(const struct Draw__Pair_ *p1_, const struct Draw__Pair_ *p2_, const struct Draw__Pair_ *p3_)
{
        S2D_DrawTriangle(
                p1_->x_, p1_->y_, fg_r, fg_g, fg_b, fg_a,
                p2_->x_, p2_->y_, fg_r, fg_g, fg_b, fg_a,
                p3_->x_, p3_->y_, fg_r, fg_g, fg_b, fg_a
        );
}

void Draw__triangle_(const struct Draw__Point_ *p1_, const struct Draw__Point_ *p2_, const struct Draw__Point_ *p3_)
{
        S2D_DrawTriangle(
                p1_->pos_.x_, p1_->pos_.y_, p1_->color_.r_, p1_->color_.g_, p1_->color_.b_, p1_->color_.a_,
                p2_->pos_.x_, p2_->pos_.y_, p2_->color_.r_, p2_->color_.g_, p2_->color_.b_, p2_->color_.a_,
                p3_->pos_.x_, p3_->pos_.y_, p3_->color_.r_, p3_->color_.g_, p3_->color_.b_, p3_->color_.a_
        );
}


void Draw__monoquad_(const struct Draw__Pair_ *p1_, const struct Draw__Pair_ *p2_, const struct Draw__Pair_ *p3_, const struct Draw__Pair_ *p4_)
{
        S2D_DrawQuad(
                p1_->x_, p1_->y_, fg_r, fg_g, fg_b, fg_a,
                p2_->x_, p2_->y_, fg_r, fg_g, fg_b, fg_a,
                p3_->x_, p3_->y_, fg_r, fg_g, fg_b, fg_a,
                p4_->x_, p4_->y_, fg_r, fg_g, fg_b, fg_a
        );
}


void Draw__quad_(const struct Draw__Point_ *p1_, const struct Draw__Point_ *p2_, const struct Draw__Point_ *p3_, const struct Draw__Point_ *p4_)
{
        S2D_DrawQuad(
                p1_->pos_.x_, p1_->pos_.y_, p1_->color_.r_, p1_->color_.g_, p1_->color_.b_, p1_->color_.a_,
                p2_->pos_.x_, p2_->pos_.y_, p2_->color_.r_, p2_->color_.g_, p2_->color_.b_, p2_->color_.a_,
                p3_->pos_.x_, p3_->pos_.y_, p3_->color_.r_, p3_->color_.g_, p3_->color_.b_, p3_->color_.a_,
                p4_->pos_.x_, p4_->pos_.y_, p4_->color_.r_, p4_->color_.g_, p4_->color_.b_, p4_->color_.a_
        );
}


void Draw__monoline_(const struct Draw__Pair_ *p1_, const struct Draw__Pair_ *p2_, OBNC_INTEGER width_)
{
    S2D_DrawLine(
        p1_->x_, p1_->y_,
        p2_->x_, p2_->y_,
        width_,
        fg_r, fg_g, fg_b, fg_a,
        fg_r, fg_g, fg_b, fg_a,
        fg_r, fg_g, fg_b, fg_a,
        fg_r, fg_g, fg_b, fg_a
    );
}

void Draw__line_(const struct Draw__Point_ *p1_, const struct Draw__Point_ *p2_, OBNC_INTEGER width_)
{
    S2D_DrawLine(
        p1_->pos_.x_, p1_->pos_.y_,
        p2_->pos_.x_, p2_->pos_.y_,
        width_,
        p1_->color_.r_, p1_->color_.g_, p1_->color_.b_, p1_->color_.a_,
        p1_->color_.r_, p1_->color_.g_, p1_->color_.b_, p1_->color_.a_,
        p2_->color_.r_, p2_->color_.g_, p2_->color_.b_, p2_->color_.a_,
        p2_->color_.r_, p2_->color_.g_, p2_->color_.b_, p2_->color_.a_
    );
}


void Draw__monocircle_(const struct Draw__Pair_ *center_, OBNC_INTEGER radius_)
{
    S2D_DrawCircle(
        center_->x_, center_->y_, radius_, 32,
        fg_r, fg_g, fg_b, fg_a
    );
}


void Draw__circle_(const struct Draw__Point_ *center_, OBNC_INTEGER sectors_, OBNC_INTEGER radius_)
{
    S2D_DrawCircle(
        center_->pos_.x_, center_->pos_.y_, radius_, sectors_,
        center_->color_.r_,
        center_->color_.g_,
        center_->color_.b_,
        center_->color_.a_
    );
}


void Draw__Init(void)
{
        static int initialized = 0;
        if (initialized == 0)
                initialized = 1;

}


void Draw__viewsize_(const struct Draw__Pair_ *size_)
{
    window->viewport.width = size_->x_;
    window->viewport.height = size_->y_;
}

void Draw__viewmode_(OBNC_INTEGER mode_)
{
    window->viewport.mode = mode_;
}

void Draw__viewposition_(OBNC_INTEGER position_)
{
}

void Draw__vsync_(int v_)
{
    window->vsync = v_;
}

void Draw__icon_(const char img_[], OBNC_INTEGER img_len)
{
    char *x = (char *)malloc(img_len + 1);
    memcpy(x, img_, img_len + 1);
    window->icon = x;
}

void Draw__loopms_(OBNC_INTEGER ms_)
{
    window->loop_ms = ms_;
}

void Draw__delayms_(OBNC_INTEGER ms_)
{
    window->delay_ms = ms_;
}

void Draw__fps_(OBNC_REAL fps_)
{
    window->fps = fps_;
}

void Draw__fpscap_(OBNC_INTEGER cap_)
{
    window->fps_cap = cap_;
}

void Draw__screenshot_(const char filepath_[], OBNC_INTEGER filepath_len)
{
    S2D_Screenshot(window, filepath_);
}

void Draw__close_()
{
    S2D_Close(window);
}

void Draw__dispose_()
{
    S2D_FreeWindow(window);
}

Draw__Text_ Draw__textcreate_(const char text_[], OBNC_INTEGER text_len, const char font_[], OBNC_INTEGER font_len, OBNC_INTEGER fontsize_)
{
    S2D_Text *s = S2D_CreateText(font_, text_, fontsize_);
    return (Draw__Text_)s;
}


void Draw__textmove_(Draw__Text_ text_, const struct Draw__Pair_ *position_)
{
    S2D_Text *s = (S2D_Text *)text_;
    s->x = position_->x_;
    s->y = position_->y_;
}


void Draw__textrotate_(Draw__Text_ text_, OBNC_INTEGER angle_, OBNC_INTEGER center_)
{
    S2D_Text *s = (S2D_Text *)text_;
    S2D_RotateText(s, angle_, center_);
}

void Draw__textcolor_(Draw__Text_ text_, const struct Draw__Color_ *color_)
{
    S2D_Text *s = (S2D_Text *)text_;
    s->color.r = color_->r_;
    s->color.g = color_->g_;
    s->color.b = color_->b_;
    s->color.a = color_->a_;
}


void Draw__textlabel_(Draw__Text_ text_, const char label_[], OBNC_INTEGER label_len)   
{
    S2D_Text *s = (S2D_Text *)text_;
    S2D_SetText(s, label_);
}


void Draw__textdispose_(Draw__Text_ text_)
{
    S2D_Text *s = (S2D_Text *)text_;
    S2D_FreeText(s);    
}

void Draw__drawtext_(Draw__Text_ text_)
{
    S2D_Text *s = (S2D_Text *)text_;
    S2D_DrawText(s);
}

Draw__Image_ Draw__imagecreate_(const char image_[], OBNC_INTEGER image_len)
{
    S2D_Image *s = S2D_CreateImage(image_);
    return (Draw__Image_)s;
}

void Draw__imagemove_(Draw__Image_ image_, const struct Draw__Pair_ *position_)
{
    S2D_Image *s = (S2D_Image *)image_;
    s->x = position_->x_;
    s->y = position_->y_;
}

void Draw__imagesize_(Draw__Image_ image_, const struct Draw__Pair_ *size_)
{
    S2D_Image *s = (S2D_Image *)image_;
    s->width = size_->x_;
    s->height = size_->y_;
}

void Draw__imagerotate_(Draw__Image_ image_, OBNC_INTEGER angle_, OBNC_INTEGER center_)
{
    S2D_Image *s = (S2D_Image*)image_;
    S2D_RotateImage(s, angle_, center_);
}

void Draw__imagecolor_(Draw__Image_ image_, const struct Draw__Color_ *color_)
{
    S2D_Image *s = (S2D_Image *)image_;
    s->color.r = color_->r_;
    s->color.g = color_->g_;
    s->color.b = color_->b_;
    s->color.a = color_->a_;
}

void Draw__drawimage_(Draw__Image_ image_)
{
    S2D_Image *s = (S2D_Image *)image_;
    S2D_DrawImage(s);
}

void Draw__imagedispose_(Draw__Image_ image_)
{
    S2D_Image *s = (S2D_Image *)image_;
    S2D_FreeImage(s);    
}

void Draw__keydown_(Draw__Key_ fn_)
{
    keydown_fn = (void (*)(long int))fn_;
}

void Draw__keyheld_(Draw__Key_ fn_)
{
    keyheld_fn = (void (*)(long int))fn_;
}

void Draw__keyup_(Draw__Key_ fn_)
{
    keyup_fn = (void (*)(long int))fn_;
}

void Draw__mousedown_(Draw__MouseEvent_ fn_)
{
    mousedown_fn = fn_;
}

void Draw__mouseup_(Draw__MouseEvent_ fn_)
{
    mouseup_fn = fn_;
}

void Draw__mousescroll_(Draw__MouseScrollEvent_ fn_)
{
    mousescroll_fn = fn_;
}

void Draw__mousemove_(Draw__MouseMoveEvent_ fn_)
{
    mousemove_fn = fn_;
}
