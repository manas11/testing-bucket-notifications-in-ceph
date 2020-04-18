// Header files for using Aws functions
#include <aws/core/Aws.h>
#include <aws/sns/SNSClient.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/http/Scheme.h>
#include <aws/sns/model/PublishRequest.h>
#include <aws/sns/model/PublishResult.h>
#include <aws/core/auth/AWSCredentials.h>

// Essential header files for C++
#include <iostream>

// Header file for the http post server
#include "httplib.h"

using namespace httplib;

int main(int argc, char **argv)
{
    // Check if the command line arguments are correct or not
    if (argc != 2)
    {
        std::cout << "Usage: adapter <sns topic arn> " << std::endl;
        return 1;
    }

    // Initialize the server object
    Server svr;

    // Set port as 8080
    auto port = 8080;

    // Initialization of AWS SDK
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        // Pick SNS ARN from command line arguments
        Aws::String topic_arn = argv[1];

        // Initialize the SNSClient
        Aws::SNS::SNSClient sns;

        // Create object to make publish request
        Aws::SNS::Model::PublishRequest psms_req;

        //To keep count of number of messages published
        int i = 0;

        //Initial message
        Aws::String message = Aws::String("Initial Message From Manas");
        psms_req.SetMessage(message);

        // Set topic ARN
        psms_req.SetTopicArn(topic_arn);

        //Publish initial message
        auto psms_out = sns.Publish(psms_req);

        if (psms_out.IsSuccess())
        {
            i++;
            std::cout << "Message " << i << " published successfully " << std::endl;
        }
        else
        {
            std::cout << "Error while publishing message " << psms_out.GetError().GetMessage() << std::endl;
        }

        // Listen to post requests and let all variables be accesible inside the lambda
        svr.Post("/", [&](const Request &req, Response &res) {
            std::cout << "Request #" << i << " received" << std::endl
                      << req.body << std::endl
                      << std::endl;

            // Set message as the request body
            psms_req.SetMessage(Aws::String(req.body.c_str(), req.body.size()));

            // Publish the message
            auto psms_out = sns.Publish(psms_req);

            if (psms_out.IsSuccess())
            {
                i++;
                std::cout << "Message" << i << " published successfully " << std::endl;
            }
            else
            {
                std::cout << "Error while publishing message " << psms_out.GetError().GetMessage()
                          << std::endl;
            }
        });

        std::cout << "The server has started at port " << port << "..." << std::endl;
        svr.listen("127.0.0.1", port);
    }

    // Shutdown Aws SDK
    Aws::ShutdownAPI(options);
    return 0;
}
