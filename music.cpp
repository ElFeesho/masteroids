#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <vector>

using std::vector;

vector<char *> songs;

FILE *current_handle = NULL;
unsigned int csong = 0;

int debugged = 0;

void debug_print(char *msg) {
    if (debugged)
        return;

    FILE *debug = fopen("/debug2.txt", "wb");
    fwrite(msg, 1, strlen(msg), debug);
    fclose(debug);
}

static s32 file_reader(void *custom_info, void *read_start, s32 length) {
    if (!current_handle) {
        if (csong > songs.size())
            csong = 0;
        char fname[MAXPATHLEN] = {0};
        sprintf(fname, "/music/masteroids/%s", songs[csong]);
        current_handle = fopen(fname, "rb");
        if (!current_handle) {
            char msg[MAXPATHLEN] = {0};
            sprintf(msg, "couldn't open %s\n", songs[csong]);
            debug_print(msg);
            return 0;
        }
    }
    if (!read_start) {
        debug_print("Start was NULL :(\n");
        return 0;
    }
    s32 size = fread(read_start, 1, length, current_handle);
    char msg[64] = {0};
    sprintf(msg, "Read %d of mp3\n", size);
    debug_print(msg);
    if (feof(current_handle)) {
        fclose(current_handle);
        current_handle = NULL;
    }
    return size;
}

static bool music_populate_list() {
    FILE *debug = fopen("/debug.txt", "wb");
    DIR_ITER *music_dir = diropen("/music/masteroids");
    if (music_dir != NULL) {
        struct stat st;
        char fname[MAXPATHLEN] = {0};
        while (!dirnext(music_dir, fname, &st)) {
            char msg[MAXPATHLEN] = {0};
            sprintf(msg, "Checking %s\n", fname);
            fwrite(msg, 1, strlen(msg), debug);
            if (!(st.st_mode & S_IFDIR)) // Sorry no recursion
            {
                if (strncasecmp(fname + strlen(fname) - 3, "mp3", 3) == 0) {
                    songs.push_back(strdup(fname));
                    fwrite(fname, 1, strlen(fname), debug);
                    fwrite("\n", 1, 1, debug);
                }
            }
            memset(fname, 0, MAXPATHLEN);
        }
        dirclose(music_dir);
    }
    fclose(debug);
    if (songs.size() > 0)
        return true;
    return false;
}

void music_init() {
    // Basically, we scan the SD Card for music
    // in the /music/masteroids/ folder.
    // I hope /music will be used by later homebrew
    // that way it'd be easy to use custom songs
    // in several games.
    fatInitDefault();
    MP3Player_Init();
    if (music_populate_list()) {
        //Play now? Why not
        MP3Player_PlayFile(NULL, file_reader, NULL);
    }
}

void music_stop() {
    MP3Player_Stop();
    for (unsigned int i = 0; i < songs.size(); i++)
        delete (songs[i]);

    songs.clear();
    csong = 0;
    if (current_handle)
        fclose(current_handle);
    current_handle = NULL;
}
