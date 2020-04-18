# SNS Adapter

This adapter listens to HTTP Post request at a specific port, then picks the body of that request and publishes a message containing this body to the SNS Topic.

# Steps to run the adpater

## Cluster and bucket related steps

### Start the ceph cluster

Start the ceph cluster as mentioned in the root README

### Create a bucket

Create a bucket named mybucket using aws s3api command.
Assuming the bucket name to be **mybucket**

> Before using aws commands add the AWS Access Key and the Secret Key to configuration using the **aws configure** command.

```
aws --endpoint-url http://localhost:8000 s3api create-bucket --bucket mybucket
```

### Create a topic

- Create a topic with endpoint as http://127.0.0.1:8080 using boto3 library.
- Assuming the topic name as **mytopic**, run the python program by using this command:

```
./create_topic.py mytopic
```

> I have included my email address as the OpaqueData in the arguments.

**Output of this command**

```
{'ResponseMetadata': {'RetryAttempts': 0, 'HTTPStatusCode': 200, 'RequestId': 'e7c7e41c-7b8a-494b-85b7-39327d069841.4200.1', 'HTTPHeaders': {'date': 'Sat, 18 Apr 2020 09:40:22 GMT', 'content-length': '287', 'x-amz-request-id': 'tx000000000000000000001-005e9acb06-1068-default', 'content-type': 'application/xml', 'connection': 'Keep-Alive'}}, u'TopicArn': 'arn:aws:sns:default::mytopic'}
```

> **Topic arn will be arn:aws:sns:default::mytopic**

### Create a notification with filters

- Add the filters required to the **notification_filters.py**
- Assuming the notification name as **mynot**
- Now, run using this command:

```
./notification_filters.py mybucket arn:aws:sns:default::mytopic mynot
```

**Output of this command**

```
{'ResponseMetadata': {'HTTPStatusCode': 200, 'RetryAttempts': 0, 'HostId': '', 'RequestId': 'tx000000000000000000004-005e9acba0-1068-default', 'HTTPHeaders': {'date': 'Sat, 18 Apr 2020 09:42:57 GMT', 'content-length': '0', 'x-amz-request-id': 'tx000000000000000000004-005e9acba0-1068-default', 'connection': 'Keep-Alive'}}}
```

> This notification will be created for events in the mubucket and then will publish respective notification to the HTTP endpoint which was specified in the topic creation.

## Running the adapter

Now, start the adapter which listens POST requests at localhost:8080 and sends json body to the SNS topic.

**Edit the CMakeLists.txt file to include path to the AWS SDK if not setup using the steps mentioned in this README**

### Link the libraries needed
```
sudo cmake .
```

### Build 
```
sudo make
```

### Set the environment variables containing the AWS Access Key and Secret key
For example:
```
export AWS_ACCESS_KEY_ID=0555b35654ad1656d804
```
```
export AWS_SECRET_ACCESS_KEY=h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==
```

### Run the adapter specifying the topic arn as a command line argument
```
./adapter <topic arn>
```
### Now, put an object in the bucket 
Use this command for example to put object into the bucket.
```
s3cmd --host=localhost:8000 --host-bucket="localhost:8000/%(bucket)" --access_key=0555b35654ad1656d804 --secret_key=h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q== put ../../../p.py s3://mybucket --no-ssl
```
**output of put**
```
upload: '../../../p.py' -> 's3://manasbucket/p.py'  [1 of 1]
 1575 of 1575   100% in    3s   484.42 B/s  done
```

- After put-object is complete, notification is sent to the endpoint to which topic is attached and then the body of POST request is sent to the SNS topic.

**Sample Console Output**
```
Message 1 published successfully 
The server has started at port 8080...
Message2 published successfully 
Request #2 received
{"Records":[{"eventVersion":"2.2","eventSource":"ceph:s3","awsRegion":"","eventTime":"2020-04-18T13:11:48.559808Z","eventName":"s3:ObjectCreated:Put","userIdentity":{"principalId":"testid"},"requestParameters":{"sourceIPAddress":""},"responseElements":{"x-amz-request-id":"e7c7e41c-7b8a-494b-85b7-39327d069841.4200.27","x-amz-id-2":"1068-default-default"},"s3":{"s3SchemaVersion":"1.0","configurationId":"manasnot","bucket":{"name":"manasbucket","ownerIdentity":{"principalId":"testid"},"arn":"arn:aws:s3:::manasbucket","id":"e7c7e41c-7b8a-494b-85b7-39327d069841.4202.1"},"object":{"key":"p.py","size":1575,"etag":"2dd16b058f745ade156d77437962d4e4","versionId":"","sequencer":"95FC9A5E150EFA28","metadata":[{"key":"x-amz-content-sha256","val":"d654ec71963bd238455a27993bc37ac12e625891f3cd4b9971226aeb176fec28"},{"key":"x-amz-date","val":"20200418T131148Z"},{"key":"x-amz-meta-s3cmd-attrs","val":"atime:1587137850/ctime:1584684358/gid:1000/gname:manas/md5:2dd16b058f745ade156d77437962d4e4/mode:33188/mtime:1584684358/uid:1000/uname:manas"},{"key":"x-amz-storage-class","val":"STANDARD"}],"tags":[]}},"eventId":"1587215509.687476.2dd16b058f745ade156d77437962d4e4","opaqueData":"manasgupta1109@gmail.com"}]}
```