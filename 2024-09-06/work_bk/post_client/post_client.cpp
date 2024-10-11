#include <iostream>
#include <curl/curl.h>

int main()
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "hello world");
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 11); 

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
