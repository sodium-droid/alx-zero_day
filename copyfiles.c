#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

void copyFile(const char *sourcePath, const char *destinationPath) {
    FILE *sourceFile, *destinationFile;
    char buffer[1024];
    size_t bytesRead;

    // Open the source file for reading
    sourceFile = fopen(sourcePath, "rb");
    if (sourceFile == NULL) {
        perror("Failed to open source file");
        return;
    }

    // Create and open the destination file for writing
    destinationFile = fopen(destinationPath, "wb");
    if (destinationFile == NULL) {
        perror("Failed to create destination file");
        fclose(sourceFile);
        return;
    }

    // Copy the content from the source file to the destination file
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);
}
bool hasExtension(const char *filename, const char *extension) {
    const char *dot = strrchr(filename, '.');
    return dot != NULL && strcmp(dot, extension) == 0;
}

int main() {
	/*Function to copy all files with ".c" extension to
	*current working directory
	*/
    const char *sourceDirectories[] = {
"../../alx-low_level_programming/0x07-pointers_arrays_strings/",
"../../alx-low_level_programming/0x04-more_functions_nested_loops/",
"../../alx-low_level_programming/0x05-pointers_arrays_strings/",
"../../alx-low_level_programming/0x02-functions_nested_loops/",
"../../alx-low_level_programming/0x06-pointers_arrays_strings/"
};
const char *destinationDirectory = "./";

char copiedFiles[1024][256]; // Array to store copied file names
    int i, copiedFileCount = 0;

    for (i = 0; i < 3; i++) {
        DIR *dir;
        struct dirent *entry;

        dir = opendir(sourceDirectories[i]);
        if (dir == NULL) {
            perror("Failed to open source directory");
            return (1);
        }

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {
                char sourcePath[256];
                char destinationPath[256];

                snprintf(sourcePath, sizeof(sourcePath), "%s%s", sourceDirectories[i], entry->d_name);
                snprintf(destinationPath, sizeof(destinationPath), "%s%s", destinationDirectory, entry->d_name);

                // Check if the file has the ".c" extension
                if (hasExtension(entry->d_name, ".c")) {
                    // Check if the file has already been copied
                    int j, alreadyCopied = 0;

                    for (j = 0; j < copiedFileCount; j++) {
                        if (strcmp(copiedFiles[j], entry->d_name) == 0) {
                            alreadyCopied = 1;
                            break;
                        }
                    }

                    if (!alreadyCopied) {
                        copyFile(sourcePath, destinationPath);
                        // Add the copied file to the list
                        strncpy(copiedFiles[copiedFileCount], entry->d_name, sizeof(copiedFiles[copiedFileCount]));
                        copiedFileCount++;
                    }
                }
            }
        }

        closedir(dir);
    }

    return (0);
}
