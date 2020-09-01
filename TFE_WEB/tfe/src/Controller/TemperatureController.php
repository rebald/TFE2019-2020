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
     * @Route("/temperature", name="temperature")
     */
    public function index()
    {
        $temps = $this->getDoctrine()
            ->getRepository(Temperature::class)
            ->findAllSorted();

        $timeString = [];

        foreach ($temps as $value) {
            $date = $value->getCreatedAt()->format('Y-m-d H:i:s');
            array_push($timeString, [
                'celsius' => $value->getCelsius(), 
                "createdAt" => $date,
            ]);
        }

        return $this->render('temperature/index.html.twig', [
            'controller_name' => 'TemperatureController',
            'temps' => $temps,
            'tempString' => $timeString,
        ]);
    }
}
