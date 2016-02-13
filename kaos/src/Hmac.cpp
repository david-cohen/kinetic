/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <stdint.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <string>
#include "Hmac.hpp"

/**
 * Computes a SHA1 HMAC for the specified data using the specified key.  The size of the data can be
 * optionality prepended to the data before hashing.  Currently, HMAC is only generated using SHA1.
 *
 * @param   data            The data to have an HMAC computed for
 * @param   key             The key to use to generate the HMAC
 * @param   algorithm       The algorithm to use to generate the HMAC (currently ignored because only
 *                          SHA1 is supported)
 * @param   prependSize     True if the data size is to be prepended to the data before hashing
 *
 * @return  HMAC for the specified data using the specified key
 */
std::string Hmac::compute(const std::string& data, const std::string& key, HmacAlgorithm algorithm, bool prependSize) {

    /*
     * Eliminate the unused args warning for algorithm.
     */
    static_cast<void>(algorithm);

    HMAC_CTX hmacContext;
    HMAC_CTX_init(&hmacContext);
    HMAC_Init_ex(&hmacContext, key.c_str(), key.length(), EVP_sha1(), NULL);

    if (data.length() != 0) {
        if (prependSize) {
            uint32_t dataLengthBigEndian = htonl(data.length());
            HMAC_Update(&hmacContext, reinterpret_cast<unsigned char*>(&dataLengthBigEndian), sizeof(uint32_t));
        }
        HMAC_Update(&hmacContext, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    }

    unsigned char result[SHA_DIGEST_LENGTH];
    unsigned int resultLength = SHA_DIGEST_LENGTH;
    HMAC_Final(&hmacContext, result, &resultLength);
    HMAC_CTX_cleanup(&hmacContext);

    return std::string(reinterpret_cast<char*>(result), resultLength);
}
