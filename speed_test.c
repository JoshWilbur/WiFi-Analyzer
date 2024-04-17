#include <stdio.h>
#include <curl/curl.h>
#include <time.h>
#include <unistd.h>

// Before first compile run: sudo apt-get install libcurl4-openssl-dev

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

void test_download_speed() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    //char *url = "https://ash-speed.hetzner.com/100MB.bin";
    char *url = "https://link.testfile.org/PDF10MB";
    char outfilename[FILENAME_MAX] = "/dev/null"; // Change this on Windows to "NUL"
    long fileSize;
    double total_time, speed;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        clock_t start = clock();
        res = curl_easy_perform(curl);
        clock_t end = clock();

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &fileSize);
            total_time = (double)(end - start) / CLOCKS_PER_SEC;
            speed = (fileSize / total_time) / (1024 * 1024); // Speed in Mbps
            printf("%.2f Mbps\n", speed);
        } else {
            fprintf(stderr, "Curl perform error: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
        curl_easy_cleanup(curl);
    }
}

int main(void) {
    //while(1) {
        test_download_speed();
        //sleep(600); // Only speed test every 10 minutes
    //}
    return 0;
}
