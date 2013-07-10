/*
 Copyright 2009-2013 Urban Airship Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binaryform must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided withthe distribution.

 THIS SOFTWARE IS PROVIDED BY THE URBAN AIRSHIP INC``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL URBAN AIRSHIP INC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>

@class UAHTTPRequest;
typedef void (^UAHTTPConnectionSuccessBlock)(UAHTTPRequest *request);
typedef void (^UAHTTPConnectionFailureBlock)(UAHTTPRequest *request);

/**
 * Wraps NSURLRequest, to be used in conjunction with UAHTTPConnection.
 */
@interface UAHTTPRequest : NSObject {

}

@property (nonatomic, readonly, retain) NSURL *url;
@property (nonatomic, retain) NSDictionary *headers;
@property (nonatomic, copy) NSString *HTTPMethod;
@property (nonatomic, copy) NSString *username;
@property (nonatomic, copy) NSString *password;
@property (nonatomic, retain) NSMutableData *body;
@property (nonatomic, assign) BOOL compressBody;
@property (nonatomic, retain) id userInfo;

@property (nonatomic, readonly, retain) NSHTTPURLResponse *response;
@property (nonatomic, readonly, copy) NSString *responseString;
@property (nonatomic, readonly, retain) NSData *responseData;
@property (nonatomic, readonly, retain) NSError *error;

/**
 * Create a request with the URL string.
 * @param urlString The URL string.
 */
+ (UAHTTPRequest *)requestWithURLString:(NSString *)urlString;

/**
 * Create a request with the URL.
 * @param url The URL.
 */
+ (UAHTTPRequest *)requestWithURL:(NSURL *)url;

/**
 * UAHTTPRequest initializer taking a URL string.
 * @param urlString The URL string.
 */
- (id)initWithURLString:(NSString *)urlString;

/**
 * UAHTTPRequest initializer taking a URL.
 * @param url The URL.
 */
- (id)initWithURL:(NSURL *)url;

/**
 * Add a request header.
 * @param header The header string to be added.
 * @param value The value string to be added.
 */
- (void)addRequestHeader:(NSString *)header value:(NSString *)value;

/**
 * Append data to the body.
 * @param data The data to be added to the body.
 */
- (void)appendBodyData:(NSData *)data;

@end

/**
 * A wrapper for NSURLConnection implementing the NSURLConnectionDelegate protocol.
 */
@interface UAHTTPConnection : NSObject <NSURLConnectionDelegate> {

}

@property (nonatomic, retain, readonly) NSURLConnection *urlConnection;
@property (nonatomic, retain, readonly) UAHTTPRequest *request;


@property (assign, nonatomic) id delegate;
@property (nonatomic, assign) SEL successSelector;
@property (nonatomic, assign) SEL failureSelector;

@property (nonatomic, copy) UAHTTPConnectionSuccessBlock successBlock;
@property (nonatomic, copy) UAHTTPConnectionFailureBlock failureBlock;

/**
 * Class factory method for creating a UAHTTPConnection.
 * @param httpRequest An instance of UAHTTPRequest.
 */
+ (UAHTTPConnection *)connectionWithRequest:(UAHTTPRequest *)httpRequest;

+ (UAHTTPConnection *)connectionWithRequest:(UAHTTPRequest *)httpRequest
                                   delegate:(id)delegate
                                    success:(SEL)successSelector
                                    failure:(SEL)failureSelector;

/**
 * Class factory method for creating a UAHTTPConnection.
 * @param httpRequest An instance of UAHTTPRequest.
 * @param successBlock A UAHTTPConnectionSuccessBlock that will be called if the connection was successful.
 * @param failureBlock A UAHTTPConnectionFailureBlock that will be called if the connection was unsuccessful.
 *
 */
+ (UAHTTPConnection *)connectionWithRequest:(UAHTTPRequest *)httpRequest
                               successBlock:(UAHTTPConnectionSuccessBlock)successBlock
                               failureBlock:(UAHTTPConnectionFailureBlock)failureBlock;

/**
 * Set the default user agent.
 * @param userAgent The user agent string.
 */
+ (void)setDefaultUserAgentString:(NSString *)userAgent;

/**
 * Initializer with the HTTP request.
 * @param httpRequest An instance of UAHTTPRequest.
 */
- (id)initWithRequest:(UAHTTPRequest *)httpRequest;

/**
 * Start the connection asynchronously.
 */
- (BOOL)start;

/**
 * Start the connection synchronously
 */
- (BOOL)startSynchronous;

/**
 * Cancel the connection
 */
- (void)cancel;

#pragma mark -
#pragma mark NSURLConnectionDelegate

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSHTTPURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;

@end
