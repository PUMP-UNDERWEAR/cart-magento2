<?php

class RawQueryTest
{
    private function _insertOneRow($ccode, $county, $city, $tax_rate)
    {
        $query = '
            insert INTO `tax_zipcode` (
                `zipcode` ,
                `county` ,
                `city` ,
                `tax_rate`
            )
            VALUES (
            ' . '\'' . $ccode . '\', \'' . $county . '\', \'' . $city . '\', ' . $tax_rate . ')
            ON DUPLICATE KEY UPDATE `tax_rate` = ' . $tax_rate . ';';

        $connectionWrite = Mage::getSingleton('core/resource')->getConnection('core_write');
        $connectionWrite->query($query);
    }

    public function delete()
    {
        $connectionWrite = Mage::getSingleton('core/resource')->getConnection('core_write');
        $connectionWrite->raw_query(
            '      DELETE FROM table_name'
        );
    }

    public function delete2()
    {
        $connectionWrite = Mage::getSingleton('core/resource')->getConnection('core_write');
        $connectionWrite->raw_query(
            "
            DROP table table_name"
        );
    }

    public function runQuery($countyInfo, $countyName)
    {
        $connectionWrite = Mage::getSingleton('core/resource')->getConnection('core_write');
        $query = '
            UPDATE `table_name`
            SET `tax_rate` = \'' . $countyInfo['tax_percentage'] . '\',
                `auth_code` = \'' . $countyInfo['auth_code'] . '\'
            WHERE county = \'' . $countyName . '\'';
        $connectionWrite->query($query);

            $connectionWrite->query('CREATE TABLE Persons
                (
                PersonID int,
                LastName varchar(255),
                FirstName varchar(255),
                Address varchar(255),
                City varchar(255)
                );');
        }

    public function getQuery($period)
    {
        $this->_period = $period;

        $query = "
			select `report_data`
			FROM `trending_report`
			WHERE `created_at` <= CURDATE( )
			AND CURDATE( ) <= `expire_at`
			AND `last_for` = ' . $period . '
			ORDER BY `created_at` DESC
			LIMIT 1
		";

        return $query;
    }
}

$installer = $this;

$installer->run("
    ALTER TABLE `{$installer->getTable('enterprise_catalogpermissions/permission')}`
        CHANGE `website_id` `website_id` SMALLINT(5) UNSIGNED DEFAULT NULL,
        CHANGE `customer_group_id` `customer_group_id` SMALLINT(3) UNSIGNED DEFAULT NULL;
");

$q = <<<EOT
    select * from table_name1
EOT;

$q2 = <<<'EOT'
	select * from table_name2
EOT;

$q3 = 'select * from table_name3';
$q4 = 'Selects from database';
$q5 = '<select></select>';
