# Testing Bucket Notifications in Ceph

> Note: All steps were performed using Ubuntu 18.04.4 LTS

Bucket notifications are a way to send out notification to any external endpoint about the events happening in the S3 bucket present in the ceph cluster. These notifications are related to **object creation and removal** events. List of these events is available in [S3 notification Event Types](https://docs.ceph.com/docs/master/radosgw/s3-notification-compatibility/#event-types). Endpoints to which these notifications can be sent are **HTTP, AMQP and KAFKA endpoints**.

## Contents
* [Sending Notifications to HTTP Endpoints](#sending-notifications-to-http-endpoints-)
* [AWS SDK adapter](#aws-sdk-adapter-)
* [Setting up Ceph cluster](#setting-up-ceph-cluster-)

## Sending notifications to HTTP endpoints [&uarr;](#contents)

Bucket notification sent to a HTTP server which accepts the POST requests.
More details in [http-endpoint](https://github.com/manas11/testing-bucket-notifications-in-ceph/tree/master/http-endpoint) directory.

## AWS SDK Adapter [&uarr;](#contents) 

C++ adapter to receive HTTP messages at one end and transmit them to SNS or Lambda endpoints.

## Setting up the Ceph cluster [&uarr;](#contents)
This directory contains steps to setup ceph cluster.
