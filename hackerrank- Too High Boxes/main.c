#include <stdio.h>

// Function to calculate the volume of the box
int calculateVolume(int length, int width, int height) {
    return length * width * height;
}

int main() {
    int n, tunnelHeight;

    // Reading the number of boxes and the height of the tunnel
    printf("Enter the height of the tunnel: ");
    scanf("%d", &tunnelHeight);

    printf("Enter the number of boxes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int length, width, height;
        printf("Enter the dimensions of box %d (length width height): ", i+1);
        scanf("%d %d %d", &length, &width, &height);

        if (height < tunnelHeight) {
            int volume = calculateVolume(length, width, height);
            printf("Box %d can be transported. Volume: %d\n", i+1, volume);
        } else {
            printf("Box %d cannot be transported.\n", i+1);
        }
    }

    return 0;
}
