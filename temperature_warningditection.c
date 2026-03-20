#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define WARNING_TEMP 80000 // 80 degrees Celsius in millidegrees

int main() {
    FILE *file;
    int temp;

    while (1) {
        file = fopen(TEMP_PATH, "r");
        if (file == NULL) {
            perror("Error opening temperature file");
            return 1;
        }

        if (fscanf(file, "%d", &temp) != 1) {
            fprintf(stderr, "Error reading temperature\n");
            fclose(file);
            return 1;
        }
        fclose(file);

        //it will Convert millidegrees to Celsius for display
        float celsius = temp / 1000.0;
        printf("Current CPU Temperature: %.2f°C\n", celsius);

        if (temp >= WARNING_TEMP) {
            printf("WARNING: High CPU Temperature Detected: %.2f°C!\n", celsius);
            // Add alarm logic here (e.g., sound, email, shutdown)
        }

        sleep(2); // it Check every 2 seconds
    }
    return 0;
}
