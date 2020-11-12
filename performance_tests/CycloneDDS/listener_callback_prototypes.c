// # Listener callback prototypes

// ### Topic
void inconsistent_topic(dds_entity_t topic, const dds_inconsistent_topic_status_t status, void *arg);

// ### Subscriber
void data_on_reader(dds_entity_t subscriber, void *arg);

// ### Reader
void data_available(dds_entity_t reader, void *arg);
void requested_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg);
void sample_lost(dds_entity_t reader, const dds_sample_lost_status_t status, void *arg);
void sample_rejected(dds_entity_t reader, const dds_sample_rejected_status_t status, void *arg);
void liveliness_changed(dds_entity_t reader, const dds_liveliness_changed_status_t status, void *arg);
void requested_dealine_missed(dds_entity_t reader, const dds_requested_deadline_missed_status_t status, void *arg);
void requested_incompatible_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg);
void subscription_macthed(dds_entity_t reader, const dds_subscription_matched_status_t status, void *arg);

// ### Writer
void offered_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg);
void liveliness_lost(dds_entity_t writer, const dds_liveliness_lost_status_t status, void *arg);
void offered_deadline_missed(dds_entity_t writer, const dds_offered_deadline_missed_status_t status, void *arg);
void offered_incompatialbe_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg);
void publication_mateched(dds_entity_t writer, const dds_publication_matched_status_t status, void *arg);
