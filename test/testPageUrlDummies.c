//
// Created by masat on 12/11/2019.
//

#include "testPageUrlDummies.h"

char *getPageWithOneUrl() {
    return "<!DOCTYPE html>"
           "<html>"
           "<head>"
           "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://static.xx.fbcdn.net/rsrc.php/v3/yr/l/0,cross/CF6sxvstdG9.css?_nc_x=lw9L9KYJoRa\">"
           "</head>"
           "<body>"
           "</body>"
           "</html>";
}

char *getPageWithFewUrl() {
    return "<!DOCTYPE html>"
           "<html>"
           "<head>"
           "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://static.xx.fbcdn.net/rsrc.php/v3/yr/l/0,cross/CF6sxvstdG9.css?_nc_x=lw9L9KYJoRa\">"
           "</head>"
           "<body>"
           "<a href=\"http://chronometre.minuteur-en-ligne.fr/chronometre-en-ligne\"></a>"
           "<img class=\"picture-img image-loader is-loaded\" src=\"https://e-cdns-images.dzcdn.net/images/cover/0a560c339ec0725cc5bcc3efa2745528/264x264-000000-80-0-0.jpg\" alt=\"\" crossorigin=\"anonymous\" height=\"264\" width=\"264\">"
           "<img class=\"picture-img active image-loader is-loaded\" src=\"https://e-cdns-images.dzcdn.net/images/cover/e7cb4ad9fa5b7c7e75b31d02a09595ec/264x264-000000-80-0-0.jpg\" alt=\"\" crossorigin=\"anonymous\" height=\"264\" width=\"264\">"
           "</body>"
           "</html>";
}