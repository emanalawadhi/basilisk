/*
 ISC License

 Copyright (c) 2016-2017, Autonomous Vehicle Systems Lab, University of Colorado at Boulder

 Permission to use, copy, modify, and/or distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */

#ifndef CSS_CONFIG_MESSAGE_H
#define CSS_CONFIG_MESSAGE_H

/*! @brief Structure used to contain the configuration information for
 each sun sensor*/
typedef struct {
    double nHatBdy[3];      /*!< -- Normal unit vector for sensor in body frame*/
    double nHatStr[3];      /*!< [-] Normal unit vector for sensor in structural frame*/
    double CBias;           /*!< W  Calibration coefficient bias for CSS */
    double cssNoiseStd;     /*!< -- Measurement noise uncertainty*/
}CSSConfigFswMsg;

#endif