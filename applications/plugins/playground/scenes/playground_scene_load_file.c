#include "../playground_i.h"
#include "../playground_custom_event.h"
#include <lib/subghz/protocols/registry.h>

#define TAG "PlayGroundSceneLoadFile"

void playground_scene_load_file_on_enter(void* context) {
    furi_assert(context);
    PlayGroundState* instance = (PlayGroundState*)context;

    // Input events and views are managed by file_browser
    FuriString* save_path;
    FuriString* app_folder;

    save_path = furi_string_alloc();
    app_folder = furi_string_alloc_set_str(PLAYGROUND_PATH);

    DialogsFileBrowserOptions browser_options;
    dialog_file_browser_set_basic_options(&browser_options, PLAYGROUND_FILE_EXT, &I_sub1_10px);

    uint8_t load_result = 255;
    bool res =
        dialog_file_browser_show(instance->dialogs, save_path, app_folder, &browser_options);
#ifdef FURI_DEBUG
    FURI_LOG_D(
        TAG,
        "save_path: %s, app_folder: %s",
        furi_string_get_cstr(save_path),
        furi_string_get_cstr(app_folder));
#endif
    if(res) {
        load_result = 0;

        if(load_result == 1) {
            scene_manager_next_scene(instance->scene_manager, PlayGroundSceneStart);
        } else {
            FURI_LOG_E(TAG, "Returned error: %d", load_result);

            FuriString* dialog_msg;
            dialog_msg = furi_string_alloc_set_str("Cannot parse file");
            dialog_message_show_storage_error(instance->dialogs, furi_string_get_cstr(dialog_msg));
            scene_manager_search_and_switch_to_previous_scene(
                instance->scene_manager, PlayGroundSceneStart);

            furi_string_free(dialog_msg);
        }
    } else {
        scene_manager_search_and_switch_to_previous_scene(
            instance->scene_manager, PlayGroundSceneStart);
    }

    furi_string_free(app_folder);
    furi_string_free(save_path);
}

void playground_scene_load_file_on_exit(void* context) {
    UNUSED(context);
}

bool playground_scene_load_file_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}