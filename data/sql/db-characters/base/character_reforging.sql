DROP TABLE IF EXISTS `character_reforging`;
CREATE TABLE `character_reforging`(
	`guid` int unsigned not null,
	`item_guid` int unsigned not null,
	`stat_decrease` int unsigned not null,
    `stat_increase` int unsigned not null,
    `stat_value` int unsigned not null,
    PRIMARY KEY (`item_guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;