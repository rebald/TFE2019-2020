<?php

namespace App\Controller;

use App\Entity\Temperature;
use DateTime;
use DateTimeZone;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\Validator\Constraints\Date;

class TemperatureController extends AbstractController
{
    /**
     * @Route("/temperature/{sort}", name="temperature")
     */
    public function index(string $sort)
    {
        $now = new DateTime(null, new DateTimeZone('Europe/Brussels'));
        $nowformat = $now->format('Y-m-d H:i:s');
        $year = (int)date("Y", strtotime($nowformat));
        $month = (int)date("m", strtotime($nowformat));
        $day = (int)date("d", strtotime($nowformat));
        
        if ($sort == "week") {
            $weekBefore = $day-7;
            if ($weekBefore<0) {
                $lastweekString = $year.'-'.($month-1).'-'.($day+$weekBefore);
                $lastsort = new DateTime($lastweekString);
            }
            else {
                $lastweekString = $year.'-'.($month).'-'.($weekBefore);
                $lastsort = new DateTime($lastweekString);
            }
        }
        elseif ($sort == "month") {
            $lastmonthString = $year.'-'.($month-1).'-'.($day);
            $lastsort = new DateTime($lastmonthString);
        }
        elseif ($sort == "year") {
            $lastyearString = ($year-1).'-'.($month).'-'.($day);
            $lastsort = new DateTime($lastyearString);
        }
        else {
            $lastsort = new DateTime("0-0-0");
        }

        $temps = $this->getDoctrine()
          ->getRepository(Temperature::class)
          ->findUntil($lastsort);

        $timeString = [];

        foreach ($temps as $value) {
            $date = $value->getCreatedAt()->format('Y-m-d H:i:s');
            array_push($timeString, ['celsius' => $value->getCelsius(), "createdAt" => $date]);
        }

        return $this->render('temperature/index.html.twig', [
            'controller_name' => 'TemperatureController',
            'temps' => $temps,
            'tempString' => $timeString,
        ]);
    }
}
