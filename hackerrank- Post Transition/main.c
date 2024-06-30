#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Package structure
struct package {
    char id[21];
    int weight;
};

// Post office structure
struct post_office {
    struct package* packages;
    int package_count;
    int min_weight;
    int max_weight;
};

// Town structure
struct town {
    char name[101];
    struct post_office* offices;
    int office_count;
};

// Function prototypes
void print_all_packages(struct town t);
void send_all_acceptable_packages(struct town* source, int source_index, struct town* target, int target_index);
struct town town_with_most_packages(struct town* towns, int town_count);
struct town* find_town(struct town* towns, int town_count, char* name);

int main() {
    int n;
    scanf("%d", &n);

    struct town* towns = (struct town*)malloc(n * sizeof(struct town));

    for (int i = 0; i < n; i++) {
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].office_count);
        towns[i].offices = (struct post_office*)malloc(towns[i].office_count * sizeof(struct post_office));

        for (int j = 0; j < towns[i].office_count; j++) {
            scanf("%d %d %d", &towns[i].offices[j].package_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = (struct package*)malloc(towns[i].offices[j].package_count * sizeof(struct package));

            for (int k = 0; k < towns[i].offices[j].package_count; k++) {
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int query_type;
        scanf("%d", &query_type);

        if (query_type == 1) {
            char town_name[101];
            scanf("%s", town_name);
            struct town* t = find_town(towns, n, town_name);
            if (t) {
                print_all_packages(*t);
            }
        } else if (query_type == 2) {
            char source_town_name[101], target_town_name[101];
            int source_index, target_index;
            scanf("%s %d %s %d", source_town_name, &source_index, target_town_name, &target_index);
            struct town* source_town = find_town(towns, n, source_town_name);
            struct town* target_town = find_town(towns, n, target_town_name);
            if (source_town && target_town) {
                send_all_acceptable_packages(source_town, source_index, target_town, target_index);
            }
        } else if (query_type == 3) {
            struct town t = town_with_most_packages(towns, n);
            printf("Town with the most packages is %s\n", t.name);
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < towns[i].office_count; j++) {
            free(towns[i].offices[j].packages);
        }
        free(towns[i].offices);
    }
    free(towns);

    return 0;
}

void print_all_packages(struct town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.office_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].package_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(struct town* source, int source_index, struct town* target, int target_index) {
    struct post_office* src_office = &source->offices[source_index];
    struct post_office* tgt_office = &target->offices[target_index];

    // Temporary storage for packages
    struct package* temp_packages = (struct package*)malloc(src_office->package_count * sizeof(struct package));
    int temp_count = 0;
    int new_package_count = 0;

    // Process each package in the source office
    for (int i = 0; i < src_office->package_count; i++) {
        if (src_office->packages[i].weight >= tgt_office->min_weight &&
            src_office->packages[i].weight <= tgt_office->max_weight) {
            tgt_office->packages = (struct package*)realloc(tgt_office->packages, (tgt_office->package_count + 1) * sizeof(struct package));
            tgt_office->packages[tgt_office->package_count++] = src_office->packages[i];
        } else {
            temp_packages[temp_count++] = src_office->packages[i];
        }
    }

    // Update source office package list
    free(src_office->packages);
    src_office->packages = temp_packages;
    src_office->package_count = temp_count;
}

struct town town_with_most_packages(struct town* towns, int town_count) {
    int max_packages = 0;
    struct town* max_town = NULL;

    for (int i = 0; i < town_count; i++) {
        int total_packages = 0;
        for (int j = 0; j < towns[i].office_count; j++) {
            total_packages += towns[i].offices[j].package_count;
        }
        if (total_packages > max_packages) {
            max_packages = total_packages;
            max_town = &towns[i];
        }
    }

    return *max_town;
}

struct town* find_town(struct town* towns, int town_count, char* name) {
    for (int i = 0; i < town_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return NULL;
}
